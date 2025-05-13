/*
 * uart_handler.c
 *
 *  Created on: 2025��4��29��
 *      Author: suiyungui
 */

/* ����ͷ�ļ� */
///////////////////////////////////////////////////////////////////////////////
#include "uart_handler.h"
#include "zf_device_wireless_uart.h" // ������ߴ���ͷ�ļ�
#include "zf_common_fifo.h"

// �����Լ���FIFO���ڴ������ߴ�������
uint8 uart_get_data[64];                                                 // ���ڽ��ջ���������
uint8 fifo_get_data[64];                                                // fifo ��ȡ����������
uint8 get_data = 0;                                                  // ���ڶ�ȡ���ݱ���
uint32 fifo_data_count = 0;                                         // fifo ��ȡ���ݳ���
fifo_struct uart_data_fifo;

uint8 data_buffer[32]; // �������ݵĻ����� (���ڴ洢���յ������ߴ�������)
uint8 data_len;

// Ϊ���ߴ��ڽ�����ӵ�ȫ�ֱ���
uint8_t wireless_buffer[32];  // ���ߴ��ڽ��ջ�����
uint8_t wireless_index = 0;   // ��ǰ��������
uint8_t command_ready = 0;    // ���������־

//void Init_uart(void)
//{
//   fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64); // ��ʼ�� fifo ������
//    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);   // ��ʼ������
//    uart_rx_interrupt(UART_INDEX, 1);                   // ���� UART_INDEX ��Ӧ���ڽ����ж�

//    uart_write_string(UART_INDEX, "UART Text.");                  // ��������ַ���
//   uart_write_byte(UART_INDEX, '\r');                                   // ����س�
//    uart_write_byte(UART_INDEX, '\n');
//}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//void Send_test(void)
//{
//    fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo ���������ݳ���
//           if(fifo_data_count != 0)                                                // ������ݲ�Ϊ��
//            {
//                fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // �� fifo �е����ݶ�ȡ����������� fifo ������
//                uart_write_string(UART_INDEX, "\r\nUART get data:");                // ��������ַ���
//               uart_write_buffer(UART_INDEX, fifo_get_data, fifo_data_count);      // ������յ�������
//            }
//            system_delay_ms(10);
//            uart_write_string(UART_INDEX, "\r\nUART no data:");
//}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------------
// �������       UART_INDEX ��Ӧ���ڽ����жϴ����� �ú����� UART_INDEX ��Ӧ���������ݽ���ʱ���Զ�����
// ����˵��       void
// ���ز���       void
// ʹ��ʾ��       uart_rx_interrupt_handler();
//-------------------------------------------------------------------------------------------------------------------
//void uart_rx_interrupt_handler(void)
//{
//    uart_query_byte(UART_INDEX, &get_data);                                     // ��ȡһ���ֽ�
//}

//-------------------------------------------------------------------------------------------------------------------
// �������       ��vofa�л�ȡ���ݲ�ת��Ϊ������
// ����˵��       const uint8_t* buffer - �ַ���������
// ����˵��       uint8_t len - ����������
// ���ز���       float - �������ĸ�����
// ʹ��ʾ��       data=Get_Data(buffer, len);
//-------------------------------------------------------------------------------------------------------------------
float Get_Data(const uint8_t* buffer, uint8_t len)
{
    uint8_t data_Start_Num = 0;
    uint8_t data_End_Num = 0;
    char temp_buffer[20]; // ��ʱ�洢ת���������ַ���
    uint8_t temp_idx = 0;
    float data_return = 0.0f;

    // ���� '=' �� '!' ��ȷ�����ֵ���ֹλ��
    for (uint8_t i = 0; i < len; i++) {
        if (buffer[i] == '=') {
            data_Start_Num = i + 1;
        }
        // ע�⣺ȷ�� '!' ���ᱻ����ض�
        if (buffer[i] == '!') {
            data_End_Num = i - 1;
            break; // �ҵ��������Ϳ����˳���
        }
        // ���ѭ�������Ҳû�ҵ� '!', ˵����ʽ���ܲ��Ի����ݲ�����
        if (i == len - 1) {
             // wireless_uart_send_string("Error: End char '!' not found.\r\n"); // ����ѡ���ʹ�����ʾ
             return 0.0f; // ���� 0 �����������ʶ
        }
    }

    // ���λ����Ч��
    if (data_Start_Num == 0 || data_End_Num < data_Start_Num || data_Start_Num >= len) {
         // wireless_uart_send_string("Error: Invalid data format near '='.\r\n"); // ����ѡ���ʹ�����ʾ
        return 0.0f; // ��ʽ����
    }

    // �����ֲ��ָ��Ƶ���ʱ����������� null ��ֹ��
    temp_idx = 0;
    // ȷ������Խ����� buffer������ temp_buffer �������
    for (uint8_t i = data_Start_Num; i <= data_End_Num && i < len && temp_idx < sizeof(temp_buffer) - 1; ++i) {
        temp_buffer[temp_idx++] = buffer[i];
    }
    temp_buffer[temp_idx] = '\0'; // ��� null ��ֹ��

    // ʹ�� atof ���ַ���ת��Ϊ������
    // atof �Դ�������Ĵ����Ƿ��� 0.0���������Ҫע��
    data_return = atof(temp_buffer);

    return data_return;
}

//-------------------------------------------------------------------------------------------------------------------
// �������       ��vofa�лش������ݽ����ֱ�ֵ
// ����˵��       uint8_t* buffer - ���յ����������
// ����˵��       uint8_t len - ���������ݳ���
// ���ز���       void
// ʹ��ʾ��       Servo_PID_Adjust(buffer, len);
//-------------------------------------------------------------------------------------------------------------------
void Servo_PID_Adjust(uint8_t* buffer, uint8_t len)
{
    if (len == 0) return; // û������
    buffer[len] = '\0'; // ����������ַ���������
    // ������ֵ����
    float data_Get = Get_Data(buffer, len);

    char feedback_buffer[64]; // ���� sprintf ��ʽ�����

    // �ж�����ǰ׺ (ȷ���Ƚϳ����㹻)
    if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'P' && buffer[2] == '=') // "SP="
    {
        // **��������һ����Ϊ servo ��ȫ�ֻ�ɷ��ʵĽṹ�����**
        servo.p = data_Get;
        // ��ʽ��������Ϣ
        sprintf(feedback_buffer, "Set Servo P = %.2f\r\n",(double)servo.p);
        // ͨ�����ߴ��ڷ���
        wireless_uart_send_string(feedback_buffer);
    }
    else if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'D' && buffer[2] == '=') // "SD="
    {
        // **��������һ����Ϊ servo ��ȫ�ֻ�ɷ��ʵĽṹ�����**
        servo.d = data_Get;
        sprintf(feedback_buffer, "Set Servo D = %.2f\r\n",(double)servo.d);
        wireless_uart_send_string(feedback_buffer);
    }
    // ��������������� else if �����������Ĳ�������������� 'SI='
    // else if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'I' && buffer[2] == '=')
    // {
    //     servo.i = data_Get; // ������ servo.i
    //     sprintf(feedback_buffer, "Set Servo I = %.2f\r\n", (double)servo.i);
    //     wireless_uart_send_string(feedback_buffer);
    // }
    else
    {
        // ����յ��������Ԥ�ڵĸ�ʽ�����Է�����ʾ
        wireless_uart_send_string("Unknown �� invalid command format.\r\n");
        // Ҳ����ѡ���յ���δ֪�����ӡ������������
        // wireless_uart_send_string("Received: ");
        // wireless_uart_send_buffer(buffer, len);
        // wireless_uart_send_string("\r\n");
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������       �������ߴ��ڽ��յ�������
// ����˵��       void
// ���ز���       void
// ʹ��ʾ��       Servo_PID_Task(); // �ڵ������е���
//-------------------------------------------------------------------------------------------------------------------
void Servo_PID_task(void)
{
    uint8_t temp_buffer[32];
    uint32_t read_len = 32;
    
    // ֱ��ʹ�����ߴ���API��ȡ����
    read_len = wireless_uart_read_buffer(temp_buffer, 32);
    
    if(read_len > 0)
    {
        // ���������е�ÿ���ֽ�
        for(uint32_t i = 0; i < read_len; i++)
        {
            // ������յ����ַ�
            wireless_buffer[wireless_index++] = temp_buffer[i];
            
            // ���յ�����������򻺳����������
            if(temp_buffer[i] == '!' || wireless_index >= sizeof(wireless_buffer)-1)
            {
                // ����PID�����������������յ�������
                Servo_PID_Adjust(wireless_buffer, wireless_index);
                
                // ���ý���״̬��׼��������һ������
                wireless_index = 0;
                break;
            }
        }
    }
}

