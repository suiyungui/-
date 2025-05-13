/*
 * imu.h
 *
 *  Created on: 2025��4��22��
 *      Author: suiyungui
 */

#ifndef CODE_IMU_H_
#define CODE_IMU_H_
#include "zf_common_headfile.h"

extern uint8 zero_error_init_flag;
extern float zero_error;
extern float gyro_z_lvbo;//���ٶ��˲����ֵ
extern float Angle_yaw;//�Ƕ�
extern float d_yaw;
extern float Yaw_tuo;
extern uint8 Yaw_tuo_flag;

void zero_error_init(void);
void get_Yaw_tuo(void);
#endif /* CODE_IMU_H_ */
