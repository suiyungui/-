/*
 * imu.c
 *
 *  Created on: 2025年4月22日
 *      Author: suiyungui
 */
#include "imu.h"
float dt1=0.002;
uint8 zero_error_init_flag=0; // 零漂处理结束标志位
float zero_error_x=0;   // x轴处理零漂
float zero_error_y=0;
float zero_error_z=0;

int average_lvbo_num_gyro_z=0;  // 用于滤波
float average_lvbo_array_gyro_z[1000];
float sum_gyro_z=0;

/* 用于计算航偏角 */
float gyro_z_lvbo=0;//角速度滤波后的值
float d_yaw=0;
float Angle_yaw=0;
float Yaw_tuo=0;


float average_lvbo_gyro_z(float measure_gyro_z,int num_gyro_z)//均值滤波,均值区间长度
{
    float x_gyro_z;//队列中被挤出的数据保存在这个变量里
    if(average_lvbo_num_gyro_z>=num_gyro_z)
        average_lvbo_num_gyro_z=0;//队列长度为num_gyro_z
    x_gyro_z=average_lvbo_array_gyro_z[average_lvbo_num_gyro_z];//被挤出去的数保存下来
    average_lvbo_array_gyro_z[average_lvbo_num_gyro_z]=measure_gyro_z;//新的数据把老数据更新掉
    average_lvbo_num_gyro_z++;//索引+1
    sum_gyro_z=sum_gyro_z+measure_gyro_z-x_gyro_z;//求和
    return sum_gyro_z/num_gyro_z;//返回均值
}


void zero_error_init(void)//零漂检测——九轴
{
    if(zero_error_init_flag==0) //——————————————————————————————判断是否已经检测过零漂
    {
        system_delay_ms(500);
        imu963ra_get_gyro();    //——————————————————————————————————读取角速度
        for(int i=0;i<80000;i++)
        {
            zero_error_x+=imu963ra_gyro_x;
            zero_error_y+=imu963ra_gyro_y;
            zero_error_z+=imu963ra_gyro_z;
        }
        zero_error_x/=80000;  //————————————————————————————————————累和求均值作为零漂值
        zero_error_y/=80000;
        zero_error_z/=80000;
        zero_error_init_flag=1;
    }
}

void get_Yaw_tuo(void)//获得陀螺仪的值Yaw_tuo——九轴
{
    if(zero_error_init_flag==1)
    {
        imu963ra_get_gyro();
        gyro_z_lvbo=average_lvbo_gyro_z((imu963ra_gyro_z-zero_error_z),5);//滤波
        d_yaw=(gyro_z_lvbo/14.285)*dt1;//——————————————————————————————————微元
        if(fabs(d_yaw)<0.0003154)   //——————————————————————————————————————防抖
            d_yaw=0;
        Angle_yaw+=d_yaw;//———————————————————————————————————————————————积分
        if(Angle_yaw<0)
          Angle_yaw=Angle_yaw+360;
        if(Angle_yaw>=360)
          Angle_yaw=Angle_yaw-360;//——————————————————————————————————————限制范围在0~360
        Yaw_tuo=360-Angle_yaw;//——————————————————————————————————————————计算偏航角
            if(Yaw_tuo==360)
                Yaw_tuo=0;
        if(Yaw_tuo>180)
          Yaw_tuo=Yaw_tuo-360;
    }
}


