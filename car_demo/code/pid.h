/*
 * pid.h
 *
 *  Created on: 2025��4��18��
 *      Author: suiyungui
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "zf_common_headfile.h"


typedef struct
{
 double target; //Ŀ��ֵ
 double now; //��ǰֵ
 int p,i,d;
 double error[3];   //��һ�ε�kp�����ڼ���kd���
 int dout;
 int out;   //���

}PID;

extern PID servo;
extern PID motor;
void Servo_PIDinit(PID *pid);
void ServoPID(void);
void ServoOut(PID *pid);
#endif /* CODE_PID_H_ */
