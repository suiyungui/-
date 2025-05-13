/*
 * remote_control.c
 *
 *  Created on: 2025��4��25��
 *      Author: suiyungui
 */


/*
 * yaokong.c
 *
 *  Created on: 2023��3��15��
 *      Author: 86181
 */

#include "remote_control.h"



int16 x6f_pin_map[6] = {X6F_CH1, X6F_CH2, X6F_CH3, X6F_CH4, X6F_CH5, X6F_CH6};
//��ͨ���ߵ�ƽ��������
int16 x6f_count[6];
//��ͨ���ߵ�ƽ�������
int16 x6f_out[6];

int16 yk_cha1,yk_cha2,yk_sheet;
int start_count=0;
int stop=1;
int8 duty_demo = 0;
void yaokong_init(void)
{

    //��ʼ�����ջ�����
    gpio_init(X6F_CH1, GPI, GPIO_LOW, GPI_PULL_UP);
    gpio_init(X6F_CH2, GPI, GPIO_LOW, GPI_PULL_UP);
    gpio_init(X6F_CH3, GPI, GPIO_LOW, GPI_PULL_UP);
    gpio_init(X6F_CH4, GPI, GPIO_LOW, GPI_PULL_UP);
    gpio_init(X6F_CH5, GPI, GPIO_LOW, GPI_PULL_UP);
    gpio_init(X6F_CH6, GPI, GPIO_LOW, GPI_PULL_UP);

}

void x6f_scan(void)                 // ͨ��ɨ��
{
    for(int i = 0; i < 6; i ++)
    {
        if(gpio_get_level(x6f_pin_map[i]))
        {
            x6f_count[i]++;
        }
        else if(x6f_count[i] > 0)
        {
            x6f_out[i] = x6f_count[i];
            x6f_count[i] = 0;
        }
    }
}
/*
void x6f_scan(void)                 // ͨ��ɨ�� (�޸ĺ�ֻɨ��ͨ��3)
{
    // ��ԭ���� for ѭ������ɾ����

    // --- ������ֻ����ͨ�� 3 (���������� 2) �Ĵ��� ---
    int channel_index = 2; // ����һ������������ر�ʾ����Ҫ����������� 2

    if(gpio_get_level(x6f_pin_map[channel_index])) // ֱ�Ӽ��ͨ�� 3 ������ (x6f_pin_map[2])
    {
        x6f_count[channel_index]++; // ͨ�� 3 �ļ������� 1 (x6f_count[2])
    }
    else if(x6f_count[channel_index] > 0) // ���ͨ�� 3 ����� (x6f_count[2] > 0)
    {
        x6f_out[channel_index] = x6f_count[channel_index]; // ��ͨ�� 3 �ļ���ֵ������ (x6f_out[2] = x6f_count[2])
        x6f_count[channel_index] = 0; // ��ͨ�� 3 �ļ��������� (x6f_count[2] = 0)
    }
    // --- ͨ�� 3 ������� ---

    // ����ͨ���Ĵ��붼û�ˣ��Ͳ��ᱻɨ����
}*/
/*
void control_yk_daohang(void)
{
   if( x6f_out[2]>150)
   {
       yk_cha1= (x6f_out[0]-147)*6;


//       if(yk_cha1<100&&yk_cha1>-100)
//       {
//           pwm_set_duty(SERVO_MOTOR_PWM, 695);
//       }
//
//
//       if(yk_cha1>100&&yk_cha1<160)
//       {
//           pwm_set_duty(SERVO_MOTOR_PWM, 803);
//       }
//
//
//
//       if(yk_cha1>-160&&yk_cha1<-100)
//       {
//           pwm_set_duty(SERVO_MOTOR_PWM, 587);
//
//       }

       yk_sheet=SERVO_MOTOR_L_MIDDLE-yk_cha1;
       yk_sheet=yk_sheet>SERVO_MOTOR_R_DUTY_MAX?SERVO_MOTOR_R_DUTY_MAX:yk_sheet;
       yk_sheet=yk_sheet<SERVO_MOTOR_L_DUTY_MAX?SERVO_MOTOR_L_DUTY_MAX:yk_sheet;

       pwm_set_duty(SERVO_MOTOR_PWM, yk_sheet);

       yk_cha2= (x6f_out[1]-100)*60;
       if(yk_cha2>0)
           gpio_set_level(DIR_CH1,1);
//       if(yk_cha2<0)
//       {
//           gpio_set_level(DIR_CH1,0);
//           yk_cha2=-yk_cha2;
//       }

       pwm_set_duty(PWM_CH1,yk_cha2);
   }

//   else me_pd1();
}
*/


void yk_stop(void)
{

    if(x6f_out[2]>150)
        stop=0;             //ң��ͣ��,����
    if(x6f_out[2]<150)
        stop=1;
}


void start_stop(void)
{
    if(stop==0)                       //  ����
      {
//          if(start_count<20&&Parameter_set0.spd_duty<4000)
//          {
//          Parameter_set0.spd_duty+=100;
//          start_count++;
//          system_delay_ms(100);
//          pwm_set_duty(PWM_CH1,Parameter_set0.spd_duty);
//          }else
      //pwm_set_duty(PWM1,Parameter_set0.spd_duty);
          if(gps_sign && stop_flag == 0)
          {
              if(duty_demo <= MAX_DUTY)
                    duty_demo++;
                  motor_duty(duty_demo);
          }
      }
      if(stop == 1 || stop_flag == 1)       //��ͣ
      {
            if(duty_demo > 0)
                duty_demo--;
            motor_duty(duty_demo);
      }
      //if(stop==1||Ge>=GPS_number)       //��ͣ������ͣ��
          //pwm_set_duty(PWM1,0);
}
int stu=0;

/*  ��֪������
void dire_stu(void)
{
        if(stop==0&&stu==0)
        {
            pwm_set_duty(PWM_CH1,Parameter_set0.spd_duty);
            system_delay_ms(20);
           stu=1;
        }
}
*/

