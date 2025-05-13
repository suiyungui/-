/*
 * key.c
 *
 *  Created on: 2025年4月24日
 *      Author: suiyungui
 */

#include "key.h"


/******************************************GPS存点第一个点为相对中心点****************************************************/
/*******************************剩下依次是第一个点、第二个点.....................****************************************/


int control_decision=1;  //方案选择和存点模式    切换标志位
int loc_number=0;    //定义位置点序号   gps存储索引
int trans_back_stop_flag=0;//切换back——stop存储标志位
uint8 adjust_flag=0;  //方案选择标志位
uint8 gps_sign = 0; // 采集完成标志位
int flash_read_sign; // flash读取标志位
int final_point;
int cout3 = 0; // 用于记录存了几个gps点位
uint8 key1_state = 0;                                               // 按键动作状态
uint8 key2_state = 0;                                               // 按键动作状态
uint8 key3_state = 0;                                               // 按键动作状态
uint8 key4_state = 0;                                               // 按键动作状态
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
// 函数简介     key初始化函数
// 参数说明     void
// 返回参数     void
// 备注信息     该函数在init.c中调用
//-------------------------------------------------------------------------------------------------------------------

void key1_init(void)
{
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY1 输入 默认高电平 上拉输入
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY2 输入 默认高电平 上拉输入
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY3 输入 默认高电平 上拉输入
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // 初始化 KEY4 输入 默认高电平 上拉输入

    gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH1 输入 默认高电平 上拉输入
    gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);        // 初始化 SWITCH2 输入 默认高电平 上拉输入
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     key点位存储函数
// 参数说明     void
// 返回参数     void
// 备注信息     该函数在main.c中调用
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
        if(key4_state && !key4_state_last)    key4_flag = 1; // 检测上升沿，消抖

        key1_state_last = key1_state;
        key2_state_last = key2_state;
        key3_state_last = key3_state;
        key4_state_last = key4_state;

        if(key1_flag)   //按键1按下 切换到下一个位置点
        {
            key1_flag = 0;
            if(control_decision<=0) // 应该没什么意义
               control_decision++;
            if(control_decision>0)
            {
                loc_number++;
                //cout1++;
            }
            key_prove_buzzer();
        }


        if(key2_flag)   //按键2按下 切换到上一个位置点
        {
            key2_flag = 0;

            if(control_decision>0) // 不觉得这个判断有意义
            {
                loc_number--;
                //cout2++;
            }
            key_prove_buzzer();
        }
        if(key3_flag)   //按键3按下 存储当前位置
        {
            key3_flag = 0;
            /*  暂时用不上
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
        // 用于设置掉头、停车点位
        if(key4_flag)   //按键4按下
        {
            key4_flag = 0;
            if(control_decision>0)
            {
                if(loc_number > 0) // 只有大于0的时候才能设置结束点，小于0的时候可以调整想设置哪一位
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

void key_prove_buzzer(void) // 用于验证按键是否正常按下
{
    gpio_toggle_level(BUZZER_PIN);
    system_delay_ms(100);
    gpio_init(BUZZER_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);                        // 初始化 BUZZER_PIN 输出 默认低电平 推挽输出模式

}


