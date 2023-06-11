/*
 * uart.h
 *
 * Created: 6/6/2023 21:43:51
 *  Author: Infinio
 */ 

#include "serialPort.h"

#ifndef UART_H_
#define UART_H_

#define BR9600 (0x67) // 0x67=103 configura BAUDRATE=9600@16MHz
#define ERROR_UART_FULL_BUFF 1
#define TX_BUFFER_LENGTH 8
#define RX_BUFFER_LENGTH 8
static unsigned char TXindice_lectura = 0, TXindice_escritura = 0;
static unsigned char RXIndex_lectura = 0, RXIndex_escritura = 0;
static unsigned char TX_buffer [ TX_BUFFER_LENGTH ];
static unsigned char RX_buffer [ RX_BUFFER_LENGTH ];
uint8_t Error_code;

void UART_Update(void);
void UART_Write_String_To_Buffer(const char* STR_PTR);
void UART_Write_Char_To_Buffer(const char Data);
char UART_Get_Char_From_Buffer(char * ch);

void UART_Init ();
void UART_Send_Char(char dato);
uint8_t UART_Receive_data (char *dato);



#endif /* UART_H_ */