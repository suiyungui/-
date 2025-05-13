/*
 * key.c
 *
 *  Created on: 2025��4��24��
 *      Author: suiyungui
 */

#include "key.h"


/******************************************GPS����һ����Ϊ������ĵ�****************************************************/
/*******************************ʣ�������ǵ�һ���㡢�ڶ�����.....................****************************************/


int control_decision=1;  //����ѡ��ʹ��ģʽ    �л���־λ
int loc_number=0;    //����λ�õ����   gps�洢����
int trans_back_stop_flag=0;//�л�back����stop�洢��־λ
uint8 adjust_flag=0;  //����ѡ���־λ
uint8 gps_sign = 0; // �ɼ���ɱ�־λ
int flash_read_sign; // flash��ȡ��־λ
int final_point;
int cout3 = 0; // ���ڼ�¼���˼���gps��λ
uint8 key1_state = 0;                                               // ��������״̬
uint8 key2_state = 0;                                               // ��������״̬
uint8 key3_state = 0;                                               // ��������״̬
uint8 key4_state = 0;                                               // ��������״̬
uint8 switch1_state = 0;
uint8 switch2_state = 0;

uint8 key1_state_last=1;
uint8 key2_state_last=1;
uint8 key3_state_last=1;
uint8 key4_state_last=1;
uint8 switch1_state_last = 1;
uint8 switch2_state_last = 1;

uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;
//-------------------------------------------------------------------------------------------------------------------
// �������     key��ʼ������
// ����˵��     void
// ���ز���     void
// ��ע��Ϣ     �ú�����init.c�е���
//-------------------------------------------------------------------------------------------------------------------

void key1_init(void)
{
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������

    gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);        // ��ʼ�� SWITCH1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);        // ��ʼ�� SWITCH2 ���� Ĭ�ϸߵ�ƽ ��������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     key��λ�洢����
// ����˵��     void
// ���ز���     void
// ��ע��Ϣ     �ú�����main.c�е���
//-------------------------------------------------------------------------------------------------------------------
void key_task()
{
        switch1_state_last = switch1_state;
        switch2_state_last = switch2_state;

        key1_state = gpio_get_level(KEY1);
        key2_state = gpio_get_level(KEY2);
        key3_state = gpio_get_level(KEY3);
        key4_state = gpio_get_level(KEY4);

        switch1_state = gpio_get_level(SWITCH1);
        switch2_state = gpio_get_level(SWITCH2);
        if(key1_state && !key1_state_last)    key1_flag = 1;
        if(key2_state && !key2_state_last)    key2_flag = 1;
        if(key3_state && !key3_state_last)    key3_flag = 1;
        if(key4_state && !key4_state_last)    key4_flag = 1; // ��������أ�����

        key1_state_last = key1_state;
        key2_state_last = key2_state;
        key3_state_last = key3_state;
        key4_state_last = key4_state;

        if(key1_flag)   //����1���� �л�����һ��λ�õ�
        {
            key1_flag = 0;
            if(control_decision<=0) // Ӧ��ûʲô����
               control_decision++;
            if(control_decision>0)
            {
                loc_number++;
                //cout1++;
            }
            key_prove_buzzer();
        }


        if(key2_flag)   //����2���� �л�����һ��λ�õ�
        {
            key2_flag = 0;

            if(control_decision>0) // ����������ж�������
            {
                loc_number--;
                //cout2++;
            }
            key_prove_buzzer();
        }
        if(key3_flag)   //����3���� �洢��ǰλ��
        {
            key3_flag = 0;
            /*  ��ʱ�ò���
            adjust_flag++;
            adjust_flag%=4;
            */
            if(control_decision>0)
            {
                la[loc_number]=gnss.latitude;
                lo[loc_number]=gnss.longitude;
                cout3++;
            }
            key_prove_buzzer();
        }
        // �������õ�ͷ��ͣ����λ
        if(key4_flag)   //����4����
        {
            key4_flag = 0;
            if(control_decision>0)
            {
                if(loc_number > 0) // ֻ�д���0��ʱ��������ý����㣬С��0��ʱ����Ե�����������һλ
                {
                    switch (trans_back_stop_flag)
                    {
                      case 0:
                          back_number=loc_number;
                      break;
                      case 1:
                          stop_number=loc_number;
                      break;;
                     }
                }
             trans_back_stop_flag++;
             trans_back_stop_flag%=2;
                 //cout4++;
            }
            //cout4++;
            key_prove_buzzer();
        }


        if(switch1_state != switch1_state_last)
        {
            gps_sign=switch1_state;
        }
                 if(switch2_state != switch2_state_last)
        {
            flash_read_sign=switch2_state;
        }
}

void key_prove_buzzer(void) // ������֤�����Ƿ���������
{
    gpio_toggle_level(BUZZER_PIN);
    system_delay_ms(100);
    gpio_init(BUZZER_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);                        // ��ʼ�� BUZZER_PIN ��� Ĭ�ϵ͵�ƽ �������ģʽ

}


