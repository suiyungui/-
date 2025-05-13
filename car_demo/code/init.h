/*
 * init.h
 *
 *  Created on: 2025年4月25日
 *      Author: suiyungui
 */

#ifndef CODE_INIT_H_
#define CODE_INIT_H_

#include "zf_common_headfile.h"
void System_Init(void);
/* 屏幕宏定义 */
#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8) // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8
/* 蜂鸣器宏定义 */
#define BUZZER_PIN              (P33_10)                                         // 定义主板蜂鸣器引脚
/* 按键宏定义 */
#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

#define SWITCH1                 (P33_11)
#define SWITCH2                 (P33_12)
/* 电机宏定义 */
#define MAX_DUTY            (20  )                                               // 最大 MAX_DUTY% 占空比
#define DIR1                (P21_4)
#define PWM1                (ATOM0_CH3_P21_5)
#define DIR2                (P02_6)
#define PWM2                (ATOM0_CH7_P02_7)
/* 舵机宏定义 */
#define SERVO_MOTOR_FREQ            (50 )      // 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
#define l_max  840
#define mid    740
#define r_max  640

#endif /* CODE_INIT_H_ */
