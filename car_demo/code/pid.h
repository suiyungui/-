/*
 * pid.h
 *
 *  Created on: 2025年4月18日
 *      Author: suiyungui
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_headfile.h"


typedef struct
{
 double target; //目标值
 double now; //当前值
 int p,i,d;
 double error[3];   //上一次的kp误差、用于计算kd误差
 int dout;
 int out;   //输出

}PID;

extern PID servo;
extern PID motor;
void Servo_PIDinit(PID *pid);
void ServoPID(void);
void ServoOut(PID *pid);
#endif /* CODE_PID_H_ */
