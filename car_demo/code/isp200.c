/*
 * isp200.c
 *
 *  Created on: 2025年4月24日
 *      Author: suiyungui
 */

 #include "isp200.h"

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     show_out函数
// 参数说明     void
// 返回参数     void
// 备注信息     屏幕显示
//-------------------------------------------------------------------------------------------------------------------

void show_task(void)

{
                    ips200_show_string(0, 16*1, "target:");
                    ips200_show_float(120, 16*1, servo.target, 4, 6);

                    ips200_show_string(0, 16*2, "Yaw:");
                    ips200_show_float(120,16*2, Yaw_tuo, 4, 6);

                    ips200_show_string(0, 16*3, "now_longitude:");
                    ips200_show_float(120, 16*3, gnss.longitude, 4, 6);

                    ips200_show_string(0, 16*4, "now_latitude:");
                    ips200_show_float(120, 16*4, gnss.latitude, 4, 6);

                    ips200_show_string(0, 16*5, "satellite:");
                    ips200_show_uint( 120, 16*5, gnss.satellite_used, 5);

                    ips200_show_string(0, 16*6, "loc_num:");
                    ips200_show_int(80, 16*6, loc_number, 3);

                    ips200_show_string(120, 16*6, "key_prove:");
                    ips200_show_int(200, 16*6, cout3, 3);

                    ips200_show_string(0, 16*7, "back_num:");
                    ips200_show_int(80, 16*7, back_number, 3);

                   ips200_show_string(120, 16*7, "stop_num:");
                    ips200_show_int(200, 16*7, stop_number, 3);


                    ips200_show_string(0, 16*8, "point_number1:");
                    ips200_show_int(120, 16*8,point_number1, 3);


                    ips200_show_string(0, 16*9, "target_longitude:");
                    ips200_show_float(135, 16*9, lo[point_number1], 4, 6);

                    ips200_show_string(0, 16*10, "target_latitude:");
                    ips200_show_float(135, 16*10, la[point_number1], 4, 6);

                    ips200_show_string(0, 16*11, "target_distance:");
                    ips200_show_float(135,16*11,get_two_points_distance(gnss.latitude,gnss.longitude, la[point_number1], lo[point_number1]),4,6);

                    ips200_show_string(0, 16*12, "target_azimuth:");
                    ips200_show_float(135,16*12, get_two_points_azimuth(gnss.latitude,gnss.longitude,la[point_number1], lo[point_number1]),4,6);

                    ips200_show_string(0, 16*13, "back/stop_point:");
                    ips200_show_int(135,16*13,trans_back_stop_flag ,3);
//
//                    ips200_show_string(0,16*17,"approach  :");
//                    ips200_show_int(140,16*   17,adjust_flag+1,5);

                    //ips200_show_int(0,16*18,bldc_flag,5);
                    //ips200_show_int(80,16*18,servo_flag,5);


                   // system_delay_ms(500);
                    //ips200_clear();
}



//-------------------------------------------------------------------------------------------------------------------
// 函数简介     show_control_choose函数
// 参数说明     void
// 返回参数     void
// 备注信息     该函数在main.c中调用
//-------------------------------------------------------------------------------------------------------------------
/*
void show_control_choose(void)
{
                    ips200_show_string(90, 16*1, "Mode_Control");
                    ips200_show_string(0, 16*2, "Make sure: Yaw to  0  !!!");

                    ips200_show_string(0, 16*3, "Yaw:");
                    ips200_show_float(140,16*3, Yaw_tuo, 4, 6);

                    ips200_show_string(0,16*4,"1  speed_gps   :");
                    ips200_show_int(180,16*4,speed_high,5);

                    ips200_show_string(0,16*5,"2  decrease_M  :");
                    ips200_show_float(140,16*5,M_0,4,6);
                    ips200_show_string(0,16*6,"4  decrease_dd :");
                    ips200_show_int(140,16*6,dd,5);

                    ips200_show_string(0,16*7,"5  increase_DD :");
                    ips200_show_int(140,16*7,DD,5);








                    ips200_show_string(0,16*15,"approach_adjust_flag:");
                    ips200_show_int(180,16*15,adjust_flag,5);

                    ips200_show_string(0,16*16,"decide_change:");
                    ips200_show_int(140,16*16,decide_change,5);

                    ips200_show_string(0,16*17,"mode_control_flag   :");
                    ips200_show_int(180,16*17,control_flag,5);

                    ips200_show_string(0,16*18,"control_decision:");
                    ips200_show_int(140,16*18,control_decision,5);

                    system_delay_ms(500);
                    ips200_clear();



}
*/

