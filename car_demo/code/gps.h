/*
 * gps.h
 *
 *  Created on: 2025��4��21��
 *      Author: suiyungui
 */

#ifndef CODE_GPS_H_
#define CODE_GPS_H_

#include "zf_common_headfile.h"
extern double  la[400];   //�洢Ŀ���γ����Ϣ
extern double  lo[400];   //�洢Ŀ��㾭����Ϣ
extern int point_number1; //λ�õ�
extern int back_number;    //����ת�䷵��λ�õ����
extern int stop_number;    //�����յ�ֹͣλ�õ����
extern double m;      //��ǰ�㵽Ŀ������
extern double ca;    //Ŀ�귽��Ƕ�
extern double cha;   //��λ����ʵ�����нǶȵĲ�ֵ
extern double j;      //���㷽λ��
extern int num;   //��ǰ��λ��num+1Ϊǰ����һĿ��
extern int stop_flag;
void get_distance(float dir,double lat,double lon, double la1,double lo1,double la[],double lo[]);
void gps_task(void);

#endif /* CODE_GPS_H_ */
