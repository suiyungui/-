/*
 * motor.c
 *
 *  Created on: 2025年4月20日
 *      Author: suiyungui
 */
#include "motor.h"
/*
#define MAX_DUTY            (30 )                                               // 最大 MAX_DUTY% 占空比
#define DIR1                (P21_4)
#define PWM1                (ATOM0_CH3_P21_5)
#define DIR2                (P02_6)
#define PWM2                (ATOM0_CH7_P02_7)
*/
int8 duty = 0;
bool dir = true;

void motor_init(void)
{
    gpio_init(DIR1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO 初始化为输出 默认上拉输出高
    gpio_init(DIR2, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM1, 17000, 0);                                                   // PWM 通道初始化频率 17KHz 占空比初始为 0
    pwm_init(PWM2, 17000, 0);                                                   // PWM 通道初始化频率 17KHz 占空比初始为 0
}
void motor_duty(int8 duty)
{

        if(duty >= 0)                                                           // 正转
        {
            //gpio_set_level(DIR1, GPIO_LOW);                                    // DIR输出高电平
            //pwm_set_duty(PWM1, duty * (PWM_DUTY_MAX / 100));                    // 计算占空比
            gpio_set_level(DIR2, GPIO_HIGH);                                    // DIR输出高电平
            pwm_set_duty(PWM2, duty * (PWM_DUTY_MAX / 100));                    // 计算占空比
        }
        else                                                                    // 反转
        {
            gpio_set_level(DIR1, GPIO_HIGH);                                     // DIR输出低电平
            pwm_set_duty(PWM1, (-duty) * (PWM_DUTY_MAX / 100));                 // 计算占空比
            gpio_set_level(DIR2, GPIO_HIGH);                                     // DIR输出低电平
            pwm_set_duty(PWM2, (-duty) * (PWM_DUTY_MAX / 100));                 // 计算占空比
        }
}

void motor_task(void)
{
    if(gps_sign && stop_flag == 0) // 采集完数据
    {
        if(duty <= MAX_DUTY)
           duty++;
        motor_duty(duty);
    }
}




