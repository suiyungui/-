/*
 * remote_control.h
 *
 *  Created on: 2025年4月25日
 *      Author: suiyungui
 */

#ifndef CODE_REMOTE_CONTROL_H_
#define CODE_REMOTE_CONTROL_H_
#include "zf_common_headfile.h"

#define X6F_CH1                     (P33_6)      //方向舵通道
#define X6F_CH2                     (P33_7)      //油门通道
#define X6F_CH3                     (P21_4)      //指示按钮通道
#define X6F_CH4                     (P21_2)      //拨动挡位通道
#define X6F_CH5                     (P21_5)      //旋钮通道1
#define X6F_CH6                     (P21_3)      //旋钮通道2

extern int16 x6f_pin_map[6];
//各通道高电平计数变量
extern int16 x6f_count[6];

//各通道高电平计数输出
extern int16 x6f_out[6];
extern int16 yk_cha1,yk_cha2,yk_flag[6],yk_sheet;
extern int stop,stu;

void yaokong_init(void);
void x6f_scan(void);
void control_yk_daohang(void);
void yk_stop(void);
void start_stop(void);
void dire_stu(void);

#endif /* CODE_REMOTE_CONTROL_H_ */
