/*
 * uart_handler.h
 *
 *  Created on: 2025年4月29日
 *      Author: suiyungui
 */

#ifndef CODE_UART_HANDLER_H_
#define CODE_UART_HANDLER_H_

#include "zf_common_headfile.h"
//void Init_uart(void);
//void Send_test(void);
float Get_Data(const uint8_t* buffer, uint8_t len);
void Servo_PID_Adjust(uint8_t* buffer, uint8_t len);
extern uint8 uart_get_data[64];                                                        // 串口接收数据缓冲区
extern uint8 fifo_get_data[64];                                                        // fifo 输出读出缓冲区

extern uint8  get_data;                                                      // 接收数据变量
extern uint32 fifo_data_count;                                        // fifo 数据个数

extern fifo_struct uart_data_fifo;
extern uint8 data_buffer[32]; // 无线串口接收缓冲区 (大小根据您的最长命令调整)
extern uint8 data_len;
void Servo_PID_task(void);
#define UART_INDEX              (DEBUG_UART_INDEX   )                           // 默认 UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // 默认 115200
#define UART_TX_PIN             (DEBUG_UART_TX_PIN  )                           // 默认 UART0_TX_P14_0
#define UART_RX_PIN             (DEBUG_UART_RX_PIN  )




#endif /* CODE_UART_HANDLER_H_ */
