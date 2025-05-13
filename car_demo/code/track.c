/*
 * track.c
 *
 *  Created on: 2025年4月27日
 *      Author: suiyungui
 */

/* 寻迹部分 */
#include "track.h"

double M_0=1.0;      //寻迹距离限制
double M_1=2.0;      //判定掉头点提前减速
double M_2=0.5;      //判定到达调头点切换下一点
//int speed_high=3000;  //gps速度
//int speed_low=1500;  //gps低速


