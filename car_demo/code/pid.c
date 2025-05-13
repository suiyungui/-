/*
 * pid.c
 *
 *  Created on: 2025年4月18日
 *      Author: suiyungui
 */
#include "pid.h"
/*
#define SERVO_MOTOR_FREQ            (50 )      // 定义主板上舵机频率  请务必注意范围 50-300
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
#define l_max  840  //1010
#define mid    740  //920
#define r_max  640  //830
*/
int temp = 740;
int flag = 0;
PID servo;
PID motor;




/*
void Motor_PIDinit(PID *pid)  //电机PID初始化函数
{


    pid->target=800;    //定义速度目标值
    pid->p=6;           //定义P、I、D参数
    pid->i=30;
    pid->d=150;
    pid->out=0;
    pid->now=0;
    pid->error[0]=0;
    pid->error[1]=0;
    pid->error[2]=0;
}
*/

void Servo_PIDinit(PID *pid)  //舵机PD初始化函数
{
    pid->target=0;
    pid->p=2.2;
    pid->i=0;
    pid->d=1;
    pid->out=0;
    pid->now=0;
    pid->error[0]=0;
    pid->error[1]=0;
    pid->error[2]=0;
}

/* pid后直接控制舵机 */
void ServoPID(void)//舵机控制  该函数放在定时器中断里
{
     if(gps_sign && stop_flag == 0) // 采集完数据并且没有到结束点
     {
        // get_distance(gnss.direction,gnss.latitude,gnss.longitude,la[point_number1],lo[point_number1],la,lo);
         servo.now=Yaw_tuo;
         servo.target=ca;
         ServoOut(&servo);
         pwm_set_duty(ATOM1_CH1_P33_9,servo.out);
         //JustFloat_Test_four(ca, Yaw_tuo, (float)servo.out, cha);//无线串口 不使用无线串口的时候要注释掉，不然程序会卡顿
     }
}

/*
void MotorOut(PID *pid)//增量式 PID控制
{

    pid->error[0]=pid->target - pid->now;

    pid->dout=(int)((pid->p*(pid->error[0]-pid->error[1])+pid->i*(pid->error[0])+pid->d*(pid->error[0]-2*pid->error[1]+pid->error[2])));

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];

    pid->out+=pid->dout;

    if(pid->out >50000)     //防止占空比给错
    {
        pid->out=50000;
    }
    if(pid->out<-50000)     //防止占空比给错
    {
        pid->out=-50000;
    }
}
*/



void ServoOut(PID *pid)//位置式 PID控制
{

    pid->error[0]=pid->now -pid->target;

    if(pid->error[0]>180)
    {
      pid->error[0]=-360+pid->error[0];
    }
    else if(pid->error[0]<-180)
    {
      pid->error[0]=360+pid->error[0];
    }

      pid->out=(int)(pid->p*pid->error[0]+pid->d*(pid->error[0]-pid->error[1])+mid);   //舵机输出
      pid->error[1] = pid->error[0];

     if(pid->out>=l_max)     //限制最大角度
      {
          pid->out=l_max;
      }
     if(pid->out<=r_max)     //限制最大角度
      {
          pid->out=r_max;
      }
}




