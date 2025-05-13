/*
 * gps.h
 *
 *  Created on: 2025年4月21日
 *      Author: suiyungui
 */

#ifndef CODE_GPS_H_
#define CODE_GPS_H_

#include "zf_common_headfile.h"
extern double  la[400];   //存储目标点纬度信息
extern double  lo[400];   //存储目标点经度信息
extern int point_number1; //位置点
extern int back_number;    //定义转弯返回位置点序号
extern int stop_number;    //定义终点停止位置点序号
extern double m;      //当前点到目标点距离
extern double ca;    //目标方向角度
extern double cha;   //方位角与实际运行角度的差值
extern double j;      //两点方位角
extern int num;   //当前点位；num+1为前进下一目标
extern int stop_flag;
void get_distance(float dir,double lat,double lon, double la1,double lo1,double la[],double lo[]);
void gps_task(void);

#endif /* CODE_GPS_H_ */
