/*
 * gps.c
 *
 *  Created on: 2025��4��21��
 *      Author: suiyungui
 */

#include "gps.h"
double  la[400];   //�洢Ŀ���γ����Ϣ
double  lo[400];   //�洢Ŀ��㾭����Ϣ

int point_number1; //λ�õ�
int num;   //��ǰ��λ��num+1Ϊǰ����һĿ��
int back_number = -1;    //����ת�䷵��λ�õ����
int stop_number = -1;    //�����յ�ֹͣλ�õ����
double m=999.0;      //��ǰ�㵽Ŀ������
double ca;    //Ŀ�귽��Ƕ�
double cha;   //��λ����ʵ�����нǶȵĲ�ֵ
double j;      //���㷽λ��

int stop_flag = 0;
/* GPS�����ȡ */
void get_distance(float dir,double lat,double lon, double la1,double lo1,double la[],double lo[])
{

    j=get_two_points_azimuth(lat,lon,la1,lo1);
    cha=j-dir;
    if(cha>180){cha=-360+cha;}
    if(cha<-180){cha=360+cha;}
    ca=Yaw_tuo+cha;
    if(ca>=180){ca=ca-360;}
    if(ca<=-180){ca=ca+360;}
    m=get_two_points_distance(lat,lon,la1,lo1);
    /*
    if(num==back_number)
    {
       if(m<M_1)                   //��ͷ���ж����룬��ǰ�����ٶ�
       {
             //bldc_decrease();          //����
             //point_number1=++num; //���µ�ͷ��λ��
       }
       else if(m<M_2)//�ж��Ƿ��Ѿ������ͷ��
       {
           // pit_flag7=1;         //increase��ʼ����־λ
            //pit_flag9=1;         //    ������䣬���ٱ�־λ
            //pit_flag6=1;        //decrease��ʼ����־λ
       }
    }
    */
    //else if(num==stop_number)
    if(num==stop_number)
    {
        /*
      servo_flag=0;
      bldc_flag=0;
      */
     stop_flag = 1; // ������־����
    }
    //else
    //{
      if(m<M_0)                   //��λѰ��
       {
          point_number1=++num; //�����ű�ָ��λ��
       }
    //}
}

void gps_task(void)
{
    /* �ŵ�ѭ����
    if(gnss_flag)
    {
        gnss_flag = 0;
        gnss_data_parse(); // gsp���ݽ���
    }
    */
    if(gps_sign)
    get_distance(gnss.direction,gnss.latitude,gnss.longitude,la[point_number1],lo[point_number1],la,lo);
}
