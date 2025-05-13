/*
 * init.c
 *
 *  Created on: 2025年4月25日
 *      Author: suiyungui
 */

#include "init.h"
// 初始化函数
void System_Init(void)
{
    motor_init();
    imu963ra_init();
    zero_error_init(); // imu零漂初始化
    gnss_init(GN42A);               // GN42A 为GPS模块 GN43RFA 为RTK模块
    pwm_init(ATOM1_CH1_P33_9, 50, 740); // 舵机初始化
    Servo_PIDinit(&servo); // 舵机pid初始化
    ips200_init(IPS200_TYPE); // 屏幕初始化
    key1_init();
    //yaokong_init(); // 遥控器初始化
    scheduler_init(); // 调度器初始化
}
