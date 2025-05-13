/*
 * uart_handler.h
 *
 *  Created on: 2025��4��29��
 *      Author: suiyungui
 */

#ifndef CODE_UART_HANDLER_H_
#define CODE_UART_HANDLER_H_

#include "zf_common_headfile.h"
//void Init_uart(void);
//void Send_test(void);
float Get_Data(const uint8_t* buffer, uint8_t len);
void Servo_PID_Adjust(uint8_t* buffer, uint8_t len);
extern uint8 uart_get_data[64];                                                        // ���ڽ������ݻ�����
extern uint8 fifo_get_data[64];                                                        // fifo �������������

extern uint8  get_data;                                                      // �������ݱ���
extern uint32 fifo_data_count;                                        // fifo ���ݸ���

extern fifo_struct uart_data_fifo;
extern uint8 data_buffer[32]; // ���ߴ��ڽ��ջ����� (��С����������������)
extern uint8 data_len;
void Servo_PID_task(void);
#define UART_INDEX              (DEBUG_UART_INDEX   )                           // Ĭ�� UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // Ĭ�� 115200
#define UART_TX_PIN             (DEBUG_UART_TX_PIN  )                           // Ĭ�� UART0_TX_P14_0
#define UART_RX_PIN             (DEBUG_UART_RX_PIN  )




#endif /* CODE_UART_HANDLER_H_ */
