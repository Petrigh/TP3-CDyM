#define F_CPU 16000000UL		// 16 MHz
#define BR9600 (0x67)			// 0x67=103 configura BAUDRATE=9600@16MHz

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serialPort.h"
#include "ringtones.h"
#include "menu.h"

 int main(void)
 {
	 
	 //comunicación con la ISR
	 RX_Buffer_overflow_flag=0;
	 RX_Buffer_flag = 0;
	 theme='1';
	 mostrarMenu= 1;
	 mostrarBienvenida=1;
	 menuFlag = SILENCIO;
	 // ------------------------ Timer 0 ------------------------
	 
	 // Configuro una interrupci?n cada 1 mseg
	 OCR0A = 248;			//124 para 8MHz y 248 para 16MHz
	 TCCR0A = (1<<WGM01);   // Modo CTC, clock interno, prescalador 64
	 TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC, clock interno, prescalador 64
	 TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n
	 
	 
	 // ------------------------ Timer 1 ------------------------
	 
	 TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1, modo CTC y salida por pin
	 TCCR1B|=(1<<WGM12)|(1<<CS10);
	 DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida
	 
	 SerialPort_Init(BR9600); 			// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
	 sei();								// Activo la mascara global de interrupciones (Bit I del SREG en 1)

	 while(1)
	 {
		 if(mostrarBienvenida){
			 printBienvenida();	//Imprimo mensaje de bienveniday cantidad de canciones
			 mostrarBienvenida=0;
		 }
		 if (mostrarMenu){
			 printMenu();		//Imprimo opciones
			 mostrarMenu = 0;
		 }
		 if(RX_Buffer_flag && menuFlag!=SELECCIONANDO){ // recepción NO Bloqueante
			 if(!RX_Buffer_overflow_flag){
				 opcionMenu(RX_Buffer);
				 RX_Buffer_flag=0;
			 }else{
				RX_Buffer_overflow_flag=0;
				SerialPort_Send_String("\nOverflow en comando\n ");
			 }
		 }
		 menuMef();
	 }
	 return 0;
 }

 // Rutina de Servicio de Interrupción de Byte Recibido
 ISR(USART_RX_vect){
	char receivedChar = UDR0;
	
	if (RX_Buffer_Index < MAX_BUFFER_SIZE - 1) {
		RX_Buffer[MAX_BUFFER_SIZE] = receivedChar;
		RX_Buffer_Index++;
	}else{
		RX_Buffer_overflow_flag=1;
	}
	
	if (receivedChar == '\r') {
		RX_Buffer[MAX_BUFFER_SIZE] = '\0';
		RX_Buffer_flag = 1;
		RX_Buffer_Index = 0;
	}
 }