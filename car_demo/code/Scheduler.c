/*
 * Scheduler.c
 *
 *  Created on: 2025��4��20��
 *      Author: suiyungui
 */

#include "Scheduler.h"


// ȫ�ֱ��������ڴ洢��������
uint8_t task_num;
uint32_t uwtick = 0;

typedef struct {
    void (*task_func)(void);
    uint32_t rate_ms;
    uint32_t last_run;
} task_t;

// ��̬�������飬ÿ�����������������ִ�����ڣ����룩���ϴ�����ʱ�䣨���룩
static task_t scheduler_task[] =
{
        {yk_stop,10,0},
        {key_task,5,0},    // ���� 10ms����һ��
        //{motor_task,50,0},  // ����һ������������Ϊ motor_task��ִ������Ϊ 50 ���룬��ʼ�ϴ�����ʱ��Ϊ 0
        {ServoPID,10,0}, // ���
        {start_stop,10,0}, // ң��������
        {gps_task,50,0},
        {show_task,300,0}, // isp��ʾ
        //{Servo_PID_task,10,0}
};

/**
 * @brief ��������ʼ������
 * �������������Ԫ�ظ�������������洢�� task_num ��
 */
void scheduler_init(void)
{
    // �������������Ԫ�ظ�������������洢�� task_num ��
    task_num = sizeof(scheduler_task) / sizeof(task_t);
}

/**
 * @brief ���������к���
 * �����������飬����Ƿ���������Ҫִ�С������ǰʱ���Ѿ����������ִ�����ڣ���ִ�и����񲢸����ϴ�����ʱ��
 */
void scheduler_run(void)
{
    // �������������е���������
    for (uint8_t i = 0; i < task_num; i++)
    {
        // ��ȡ��ǰ��ϵͳʱ�䣨���룩
        //uint32_t now_time = system_getval_ms();
        uint32_t now_time = uwtick;
        // ��鵱ǰʱ���Ƿ�ﵽ�����ִ��ʱ��
        if (now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
        {
            // ����������ϴ�����ʱ��Ϊ��ǰʱ��
            scheduler_task[i].last_run = now_time;

            // ִ��������
            scheduler_task[i].task_func();
        }
    }
}





