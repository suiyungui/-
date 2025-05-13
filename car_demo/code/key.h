/*
 * key.h
 *
 *  Created on: 2025Äê4ÔÂ24ÈÕ
 *      Author: suiyungui
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_
#include "zf_common_headfile.h"
extern int control_decision;
extern int loc_number;

extern int collection_sign;
extern uint8 gps_sign;
extern int flash_read_sign;
extern uint8 switch2_state;
extern uint8 switch2_state_last;
extern int final_point;
extern int trans_back_stop_flag;
extern uint8 adjust_flag;
extern int decide_change;
extern int cout3;
void key1_init(void);
void key_task();
void key_prove_buzzer(void);



#endif /* CODE_KEY_H_ */
