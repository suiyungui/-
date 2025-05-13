/*
 * remote_control.h
 *
 *  Created on: 2025��4��25��
 *      Author: suiyungui
 */

#ifndef CODE_REMOTE_CONTROL_H_
#define CODE_REMOTE_CONTROL_H_
#include "zf_common_headfile.h"

#define X6F_CH1                     (P33_6)      //�����ͨ��
#define X6F_CH2                     (P33_7)      //����ͨ��
#define X6F_CH3                     (P21_4)      //ָʾ��ťͨ��
#define X6F_CH4                     (P21_2)      //������λͨ��
#define X6F_CH5                     (P21_5)      //��ťͨ��1
#define X6F_CH6                     (P21_3)      //��ťͨ��2

extern int16 x6f_pin_map[6];
//��ͨ���ߵ�ƽ��������
extern int16 x6f_count[6];

//��ͨ���ߵ�ƽ�������
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
