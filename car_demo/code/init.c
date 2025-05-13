/*
 * init.c
 *
 *  Created on: 2025��4��25��
 *      Author: suiyungui
 */

#include "init.h"
// ��ʼ������
void System_Init(void)
{
    motor_init();
    imu963ra_init();
    zero_error_init(); // imu��Ư��ʼ��
    gnss_init(GN42A);               // GN42A ΪGPSģ�� GN43RFA ΪRTKģ��
    pwm_init(ATOM1_CH1_P33_9, 50, 740); // �����ʼ��
    Servo_PIDinit(&servo); // ���pid��ʼ��
    ips200_init(IPS200_TYPE); // ��Ļ��ʼ��
    key1_init();
    //yaokong_init(); // ң������ʼ��
    scheduler_init(); // ��������ʼ��
}
