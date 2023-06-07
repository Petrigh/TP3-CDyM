/*
 * uart.h
 *
 * Created: 6/6/2023 21:43:51
 *  Author: Infinio
 */ 


#ifndef UART_H_
#define UART_H_

static unsigned char TXindice_lectura = 0, TXindice_escritura = 0;
static unsigned char TX_BUFFER [ TX_BUFFER_LENGTH ];

void UART_Update(void);
void UART_Write_String_To_Buffer(const char* STR_PTR);
void UART_Write_Char_To_Buffer(const char Data);
char UART_Get_Char_From_Buffer(char * ch);
void UART_Init (int Baud);
void UART_Send_Char(char dato);
char UART_Receive_data (char *dato);



#endif /* UART_H_ */