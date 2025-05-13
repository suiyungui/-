/*
 * init.h
 *
 *  Created on: 2025��4��25��
 *      Author: suiyungui
 */

#ifndef CODE_INIT_H_
#define CODE_INIT_H_

#include "zf_common_headfile.h"
void System_Init(void);
/* ��Ļ�궨�� */
#define IPS200_TYPE     (IPS200_TYPE_PARALLEL8) // ˫������ ���������� ����궨����д IPS200_TYPE_PARALLEL8
/* �������궨�� */
#define BUZZER_PIN              (P33_10)                                         // �����������������
/* �����궨�� */
#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)

#define SWITCH1                 (P33_11)
#define SWITCH2                 (P33_12)
/* ����궨�� */
#define MAX_DUTY            (20  )                                               // ��� MAX_DUTY% ռ�ձ�
#define DIR1                (P21_4)
#define PWM1                (ATOM0_CH3_P21_5)
#define DIR2                (P02_6)
#define PWM2                (ATOM0_CH7_P02_7)
/* ����궨�� */
#define SERVO_MOTOR_FREQ            (50 )      // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
#define l_max  840
#define mid    740
#define r_max  640

#endif /* CODE_INIT_H_ */
