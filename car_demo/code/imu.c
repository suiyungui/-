/*
 * imu.c
 *
 *  Created on: 2025��4��22��
 *      Author: suiyungui
 */
#include "imu.h"
float dt1=0.002;
uint8 zero_error_init_flag=0; // ��Ư���������־λ
float zero_error_x=0;   // x�ᴦ����Ư
float zero_error_y=0;
float zero_error_z=0;

int average_lvbo_num_gyro_z=0;  // �����˲�
float average_lvbo_array_gyro_z[1000];
float sum_gyro_z=0;

/* ���ڼ��㺽ƫ�� */
float gyro_z_lvbo=0;//���ٶ��˲����ֵ
float d_yaw=0;
float Angle_yaw=0;
float Yaw_tuo=0;


float average_lvbo_gyro_z(float measure_gyro_z,int num_gyro_z)//��ֵ�˲�,��ֵ���䳤��
{
    float x_gyro_z;//�����б����������ݱ��������������
    if(average_lvbo_num_gyro_z>=num_gyro_z)
        average_lvbo_num_gyro_z=0;//���г���Ϊnum_gyro_z
    x_gyro_z=average_lvbo_array_gyro_z[average_lvbo_num_gyro_z];//������ȥ������������
    average_lvbo_array_gyro_z[average_lvbo_num_gyro_z]=measure_gyro_z;//�µ����ݰ������ݸ��µ�
    average_lvbo_num_gyro_z++;//����+1
    sum_gyro_z=sum_gyro_z+measure_gyro_z-x_gyro_z;//���
    return sum_gyro_z/num_gyro_z;//���ؾ�ֵ
}


void zero_error_init(void)//��Ư��⡪������
{
    if(zero_error_init_flag==0) //�������������������������������������������������������������ж��Ƿ��Ѿ�������Ư
    {
        system_delay_ms(500);
        imu963ra_get_gyro();    //����������������������������������������������������������������������ȡ���ٶ�
        for(int i=0;i<80000;i++)
        {
            zero_error_x+=imu963ra_gyro_x;
            zero_error_y+=imu963ra_gyro_y;
            zero_error_z+=imu963ra_gyro_z;
        }
        zero_error_x/=80000;  //�������������������������������������������������������������������������ۺ����ֵ��Ϊ��Ưֵ
        zero_error_y/=80000;
        zero_error_z/=80000;
        zero_error_init_flag=1;
    }
}

void get_Yaw_tuo(void)//��������ǵ�ֵYaw_tuo��������
{
    if(zero_error_init_flag==1)
    {
        imu963ra_get_gyro();
        gyro_z_lvbo=average_lvbo_gyro_z((imu963ra_gyro_z-zero_error_z),5);//�˲�
        d_yaw=(gyro_z_lvbo/14.285)*dt1;//��������������������������������������������������������������������΢Ԫ
        if(fabs(d_yaw)<0.0003154)   //��������������������������������������������������������������������������������
            d_yaw=0;
        Angle_yaw+=d_yaw;//��������������������������������������������������������������������������������������������������
        if(Angle_yaw<0)
          Angle_yaw=Angle_yaw+360;
        if(Angle_yaw>=360)
          Angle_yaw=Angle_yaw-360;//�������������������������������������������������������������������������������Ʒ�Χ��0~360
        Yaw_tuo=360-Angle_yaw;//����������������������������������������������������������������������������������������ƫ����
            if(Yaw_tuo==360)
                Yaw_tuo=0;
        if(Yaw_tuo>180)
          Yaw_tuo=Yaw_tuo-360;
    }
}


