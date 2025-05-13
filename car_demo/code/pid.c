/*
 * pid.c
 *
 *  Created on: 2025��4��18��
 *      Author: suiyungui
 */
#include "pid.h"
/*
#define SERVO_MOTOR_FREQ            (50 )      // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
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
void Motor_PIDinit(PID *pid)  //���PID��ʼ������
{


    pid->target=800;    //�����ٶ�Ŀ��ֵ
    pid->p=6;           //����P��I��D����
    pid->i=30;
    pid->d=150;
    pid->out=0;
    pid->now=0;
    pid->error[0]=0;
    pid->error[1]=0;
    pid->error[2]=0;
}
*/

void Servo_PIDinit(PID *pid)  //���PD��ʼ������
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

/* pid��ֱ�ӿ��ƶ�� */
void ServoPID(void)//�������  �ú������ڶ�ʱ���ж���
{
     if(gps_sign && stop_flag == 0) // �ɼ������ݲ���û�е�������
     {
        // get_distance(gnss.direction,gnss.latitude,gnss.longitude,la[point_number1],lo[point_number1],la,lo);
         servo.now=Yaw_tuo;
         servo.target=ca;
         ServoOut(&servo);
         pwm_set_duty(ATOM1_CH1_P33_9,servo.out);
         //JustFloat_Test_four(ca, Yaw_tuo, (float)servo.out, cha);//���ߴ��� ��ʹ�����ߴ��ڵ�ʱ��Ҫע�͵�����Ȼ����Ῠ��
     }
}

/*
void MotorOut(PID *pid)//����ʽ PID����
{

    pid->error[0]=pid->target - pid->now;

    pid->dout=(int)((pid->p*(pid->error[0]-pid->error[1])+pid->i*(pid->error[0])+pid->d*(pid->error[0]-2*pid->error[1]+pid->error[2])));

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];

    pid->out+=pid->dout;

    if(pid->out >50000)     //��ֹռ�ձȸ���
    {
        pid->out=50000;
    }
    if(pid->out<-50000)     //��ֹռ�ձȸ���
    {
        pid->out=-50000;
    }
}
*/



void ServoOut(PID *pid)//λ��ʽ PID����
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

      pid->out=(int)(pid->p*pid->error[0]+pid->d*(pid->error[0]-pid->error[1])+mid);   //������
      pid->error[1] = pid->error[0];

     if(pid->out>=l_max)     //�������Ƕ�
      {
          pid->out=l_max;
      }
     if(pid->out<=r_max)     //�������Ƕ�
      {
          pid->out=r_max;
      }
}




