/*
 * gps.c
 *
 *  Created on: 2025年4月21日
 *      Author: suiyungui
 */

#include "gps.h"
double  la[400];   //存储目标点纬度信息
double  lo[400];   //存储目标点经度信息

int point_number1; //位置点
int num;   //当前点位；num+1为前进下一目标
int back_number = -1;    //定义转弯返回位置点序号
int stop_number = -1;    //定义终点停止位置点序号
double m=999.0;      //当前点到目标点距离
double ca;    //目标方向角度
double cha;   //方位角与实际运行角度的差值
double j;      //两点方位角

int stop_flag = 0;
/* GPS距离获取 */
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
       if(m<M_1)                   //掉头点判定距离，提前降低速度
       {
             //bldc_decrease();          //减速
             //point_number1=++num; //更新调头点位置
       }
       else if(m<M_2)//判定是否已经到达调头点
       {
           // pit_flag7=1;         //increase初始化标志位
            //pit_flag9=1;         //    避免大弯，加速标志位
            //pit_flag6=1;        //decrease初始化标志位
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
     stop_flag = 1; // 结束标志拉高
    }
    //else
    //{
      if(m<M_0)                   //点位寻迹
       {
          point_number1=++num; //更新信标指令位置
       }
    //}
}

void gps_task(void)
{
    /* 放到循环里
    if(gnss_flag)
    {
        gnss_flag = 0;
        gnss_data_parse(); // gsp数据解析
    }
    */
    if(gps_sign)
    get_distance(gnss.direction,gnss.latitude,gnss.longitude,la[point_number1],lo[point_number1],la,lo);
}
