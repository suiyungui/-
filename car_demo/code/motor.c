/*
 * motor.c
 *
 *  Created on: 2025��4��20��
 *      Author: suiyungui
 */
#include "motor.h"
/*
#define MAX_DUTY            (30 )                                               // ��� MAX_DUTY% ռ�ձ�
#define DIR1                (P21_4)
#define PWM1                (ATOM0_CH3_P21_5)
#define DIR2                (P02_6)
#define PWM2                (ATOM0_CH7_P02_7)
*/
int8 duty = 0;
bool dir = true;

void motor_init(void)
{
    gpio_init(DIR1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO ��ʼ��Ϊ��� Ĭ�����������
    gpio_init(DIR2, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO ��ʼ��Ϊ��� Ĭ�����������
    pwm_init(PWM1, 17000, 0);                                                   // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0
    pwm_init(PWM2, 17000, 0);                                                   // PWM ͨ����ʼ��Ƶ�� 17KHz ռ�ձȳ�ʼΪ 0
}
void motor_duty(int8 duty)
{

        if(duty >= 0)                                                           // ��ת
        {
            //gpio_set_level(DIR1, GPIO_LOW);                                    // DIR����ߵ�ƽ
            //pwm_set_duty(PWM1, duty * (PWM_DUTY_MAX / 100));                    // ����ռ�ձ�
            gpio_set_level(DIR2, GPIO_HIGH);                                    // DIR����ߵ�ƽ
            pwm_set_duty(PWM2, duty * (PWM_DUTY_MAX / 100));                    // ����ռ�ձ�
        }
        else                                                                    // ��ת
        {
            gpio_set_level(DIR1, GPIO_HIGH);                                     // DIR����͵�ƽ
            pwm_set_duty(PWM1, (-duty) * (PWM_DUTY_MAX / 100));                 // ����ռ�ձ�
            gpio_set_level(DIR2, GPIO_HIGH);                                     // DIR����͵�ƽ
            pwm_set_duty(PWM2, (-duty) * (PWM_DUTY_MAX / 100));                 // ����ռ�ձ�
        }
}

void motor_task(void)
{
    if(gps_sign && stop_flag == 0) // �ɼ�������
    {
        if(duty <= MAX_DUTY)
           duty++;
        motor_duty(duty);
    }
}




