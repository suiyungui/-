/*
 * uart_handler.c
 *
 *  Created on: 2025年4月29日
 *      Author: suiyungui
 */

/* 包含头文件 */
///////////////////////////////////////////////////////////////////////////////
#include "uart_handler.h"
#include "zf_device_wireless_uart.h" // 添加无线串口头文件
#include "zf_common_fifo.h"

// 定义自己的FIFO用于处理无线串口数据
uint8 uart_get_data[64];                                                 // 串口接收缓冲区数组
uint8 fifo_get_data[64];                                                // fifo 读取缓冲区数组
uint8 get_data = 0;                                                  // 串口读取数据变量
uint32 fifo_data_count = 0;                                         // fifo 读取数据长度
fifo_struct uart_data_fifo;

uint8 data_buffer[32]; // 接收数据的缓冲区 (用于存储接收到的无线串口数据)
uint8 data_len;

// 为无线串口接收添加的全局变量
uint8_t wireless_buffer[32];  // 无线串口接收缓冲区
uint8_t wireless_index = 0;   // 当前接收索引
uint8_t command_ready = 0;    // 命令就绪标志

//void Init_uart(void)
//{
//   fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64); // 初始化 fifo 缓冲区
//    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);   // 初始化串口
//    uart_rx_interrupt(UART_INDEX, 1);                   // 开启 UART_INDEX 对应串口接收中断

//    uart_write_string(UART_INDEX, "UART Text.");                  // 输出测试字符串
//   uart_write_byte(UART_INDEX, '\r');                                   // 输出回车
//    uart_write_byte(UART_INDEX, '\n');
//}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//void Send_test(void)
//{
//    fifo_data_count = fifo_used(&uart_data_fifo);                           // 查看 fifo 缓冲区数据长度
//           if(fifo_data_count != 0)                                                // 如果数据不为空
//            {
//                fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // 将 fifo 中的数据读取出来并且清空 fifo 缓冲区
//                uart_write_string(UART_INDEX, "\r\nUART get data:");                // 输出测试字符串
//               uart_write_buffer(UART_INDEX, fifo_get_data, fifo_data_count);      // 输出接收到的数据
//            }
//            system_delay_ms(10);
//            uart_write_string(UART_INDEX, "\r\nUART no data:");
//}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------------
// 函数简介       UART_INDEX 对应串口接收中断处理函数 该函数在 UART_INDEX 对应串口有数据接收时会自动调用
// 参数说明       void
// 返回参数       void
// 使用示例       uart_rx_interrupt_handler();
//-------------------------------------------------------------------------------------------------------------------
//void uart_rx_interrupt_handler(void)
//{
//    uart_query_byte(UART_INDEX, &get_data);                                     // 读取一个字节
//}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介       从vofa中获取数据并转化为浮点数
// 参数说明       const uint8_t* buffer - 字符串缓冲区
// 参数说明       uint8_t len - 缓冲区长度
// 返回参数       float - 解析出的浮点数
// 使用示例       data=Get_Data(buffer, len);
//-------------------------------------------------------------------------------------------------------------------
float Get_Data(const uint8_t* buffer, uint8_t len)
{
    uint8_t data_Start_Num = 0;
    uint8_t data_End_Num = 0;
    char temp_buffer[20]; // 临时存储转换的数字字符串
    uint8_t temp_idx = 0;
    float data_return = 0.0f;

    // 查找 '=' 和 '!' 来确定数字的起止位置
    for (uint8_t i = 0; i < len; i++) {
        if (buffer[i] == '=') {
            data_Start_Num = i + 1;
        }
        // 注意：确保 '!' 不会被意外截断
        if (buffer[i] == '!') {
            data_End_Num = i - 1;
            break; // 找到结束符就可以退出了
        }
        // 如果循环到最后也没找到 '!', 说明格式可能不对或数据不完整
        if (i == len - 1) {
             // wireless_uart_send_string("Error: End char '!' not found.\r\n"); // 可以选择发送错误提示
             return 0.0f; // 返回 0 或其他错误标识
        }
    }

    // 检查位置有效性
    if (data_Start_Num == 0 || data_End_Num < data_Start_Num || data_Start_Num >= len) {
         // wireless_uart_send_string("Error: Invalid data format near '='.\r\n"); // 可以选择发送错误提示
        return 0.0f; // 格式错误
    }

    // 将数字部分复制到临时缓冲区并添加 null 终止符
    temp_idx = 0;
    // 确保不会越界访问 buffer，并且 temp_buffer 不会溢出
    for (uint8_t i = data_Start_Num; i <= data_End_Num && i < len && temp_idx < sizeof(temp_buffer) - 1; ++i) {
        temp_buffer[temp_idx++] = buffer[i];
    }
    temp_buffer[temp_idx] = '\0'; // 添加 null 终止符

    // 使用 atof 将字符串转换为浮点数
    // atof 对错误输入的处理是返回 0.0，这可能需要注意
    data_return = atof(temp_buffer);

    return data_return;
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介       将vofa中回传的数据解析分别赋值
// 参数说明       uint8_t* buffer - 接收到的命令缓冲区
// 参数说明       uint8_t len - 缓冲区数据长度
// 返回参数       void
// 使用示例       Servo_PID_Adjust(buffer, len);
//-------------------------------------------------------------------------------------------------------------------
void Servo_PID_Adjust(uint8_t* buffer, uint8_t len)
{
    if (len == 0) return; // 没有数据
    buffer[len] = '\0'; // 在这里添加字符串结束符
    // 解析数值部分
    float data_Get = Get_Data(buffer, len);

    char feedback_buffer[64]; // 用于 sprintf 格式化输出

    // 判断命令前缀 (确保比较长度足够)
    if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'P' && buffer[2] == '=') // "SP="
    {
        // **假设您有一个名为 servo 的全局或可访问的结构体变量**
        servo.p = data_Get;
        // 格式化反馈信息
        sprintf(feedback_buffer, "Set Servo P = %.2f\r\n",(double)servo.p);
        // 通过无线串口发送
        wireless_uart_send_string(feedback_buffer);
    }
    else if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'D' && buffer[2] == '=') // "SD="
    {
        // **假设您有一个名为 servo 的全局或可访问的结构体变量**
        servo.d = data_Get;
        sprintf(feedback_buffer, "Set Servo D = %.2f\r\n",(double)servo.d);
        wireless_uart_send_string(feedback_buffer);
    }
    // 您可以在这里添加 else if 来处理其他的参数调整命令，例如 'SI='
    // else if (len >= 3 && buffer[0] == 'S' && buffer[1] == 'I' && buffer[2] == '=')
    // {
    //     servo.i = data_Get; // 假设有 servo.i
    //     sprintf(feedback_buffer, "Set Servo I = %.2f\r\n", (double)servo.i);
    //     wireless_uart_send_string(feedback_buffer);
    // }
    else
    {
        // 如果收到的命令不是预期的格式，可以发送提示
        wireless_uart_send_string("Unknown 或 invalid command format.\r\n");
        // 也可以选择将收到的未知命令打印出来帮助调试
        // wireless_uart_send_string("Received: ");
        // wireless_uart_send_buffer(buffer, len);
        // wireless_uart_send_string("\r\n");
    }
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介       处理无线串口接收到的数据
// 参数说明       void
// 返回参数       void
// 使用示例       Servo_PID_Task(); // 在调度器中调用
//-------------------------------------------------------------------------------------------------------------------
void Servo_PID_task(void)
{
    uint8_t temp_buffer[32];
    uint32_t read_len = 32;
    
    // 直接使用无线串口API读取数据
    read_len = wireless_uart_read_buffer(temp_buffer, 32);
    
    if(read_len > 0)
    {
        // 处理缓冲区中的每个字节
        for(uint32_t i = 0; i < read_len; i++)
        {
            // 保存接收到的字符
            wireless_buffer[wireless_index++] = temp_buffer[i];
            
            // 接收到命令结束符或缓冲区即将溢出
            if(temp_buffer[i] == '!' || wireless_index >= sizeof(wireless_buffer)-1)
            {
                // 调用PID参数调整函数处理收到的命令
                Servo_PID_Adjust(wireless_buffer, wireless_index);
                
                // 重置接收状态，准备接收下一条命令
                wireless_index = 0;
                break;
            }
        }
    }
}

