
#include "uart.h"
 
 void UART_Update(void){
	 char dato;
	 if (TXindice_lectura < TXindice_escritura) //Hay byte en el buffer TX para transmitir?
	 {
		 //UART_Send_Char ( TX_buffer [ TXindice_lectura ] );
		 UDR0 = TX_buffer[TXindice_lectura];
		 TXindice_lectura++;
	 }
	 else
	 { //No hay dato disponibles para enviar
		 TXindice_lectura = 0;
		 TXindice_escritura = 0;
	 }
	 /*
	 //Se ha recibido algún byte?
	 if ( UART_Receive_data ( &dato ) != 0)
	 { //Byte recibido. Escribir byte en buffer de entrada
		 if ( RXIndex_escritura < RX_BUFFER_LENGTH)
		 {
			RX_buffer [ RXIndex_escritura ] = dato; //Guardar dato en buffer
			RXIndex_escritura++; //Inc sin desbordar buffer 
		 }
		 else
		 {
			 Error_code = ERROR_UART_FULL_BUFF;
			 UART_Write_String_To_Buffer("Error: Buffer del Uart lleno, se perdieron datos.\r\n");
		 }
	 }
	 else {
		 Error_code = 0;  // Reset error code if no data is received
	 }
	 */
 }
 
 void UART_Write_String_To_Buffer (const char* STR_PTR)
 {
	 char i = 0;
	 while ( STR_PTR[i] != '\0')
	 {
		 UART_Write_Char_To_Buffer( STR_PTR[i] );
		 i++;
	 }
 }
 
 void UART_Write_Char_To_Buffer (const char data)
 {
	 if (TXindice_escritura < TX_BUFFER_LENGTH)
	 {
		 TX_buffer [ TXindice_escritura ] = data;
		 TXindice_escritura++;
	 }
	 else
	 {
		 //Write buffer is full
		 Error_code = ERROR_UART_FULL_BUFF;
	 }
	 
 }  

 
 char UART_Get_Char_From_Buffer (char* ch)
 {
	//Hay nuevo dato en el buffer?
	if ( RXIndex_lectura < RXIndex_escritura )
	{
		*ch = RX_buffer [ RXIndex_lectura ];
		RXIndex_lectura++;
		return 1; //Hay nuevo dato
	}
	else
	{
		RXIndex_lectura = 0;
		RXIndex_escritura = 0;
		return 0; //No hay	
	}
 }

 
 void UART_Init ()
 {
	 //Revisar u.u
	 SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 
	 Error_code = 0;
 }


 void UART_Send_Char ( char dato )
 {
	 long Timeout = 0;
	 while(( ++Timeout ) && ((UCSR0A & (1 << UDRE0)) == 0));
	 if ( Timeout != 0 )
		UDR0 = dato;
	 else{
		// TX_UART did not respond - error 
	 }
 }
 
 uint8_t UART_Receive_data ( char *dato )
 {
	 if ( UCSR0A & (1 << RXC0) )
	 {
		 *dato = UDR0;
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }
 }
 
 
 
 
 /*
 //1-transmitir G. Ver silulador as7, tregistros uart y tiempo que tarda en transmitir un caracter.

#include <avr/io.h>
#define F_CPU 16000000UL		// 16 MHz
#include <util/delay.h>

 int main(void)
 {
	 //initialize the USART
	 UCSR0B = (1<<TXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = 'G';						 //transmit ‘G’ letter
		 //_delay_ms(500);
	 }
	 return 0;
 }
 
 
 
 //2-LOOPBACK con polling 
 #include <avr/io.h>
 #define F_CPU 16000000UL		// 16 MHz
 #include <util/delay.h>
 
 int main(void)
 {
	 volatile unsigned char dato;
	 //initialize the USART
	 UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = 'G';						 //transmit ‘G’ letter
		 while (! (UCSR0A & (1<<RXC0))); //wait until new data
		 dato = UDR0;
	 }
	 return 0;
 }
 //3-eco de caracter con polling (no se puede simular en as7 la recepcion)

 #include <avr/io.h>
 #define F_CPU 16000000UL		// 16 MHz
 #include <util/delay.h>

 int main(void)
 {
	 volatile unsigned char dato;
	 DDRB=0xFF;
	 //initialize the USART
	 UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	 UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	 UBRR0L = 103;						 //baud rate = 9600bps@16MHz
	 while(1) {
		 while (! (UCSR0A & (1<<RXC0))); //wait until new data
		 dato = UDR0;
		 while (! (UCSR0A & (1<<UDRE0))); //wait until UDR0 is empty
		 UDR0 = dato;						 //transmit dato
		 PORTB= dato;
	 }
	 return 0;
 }

 //4- transmitir cadenas +  eco

// Archivo de cabecera del Microcontrolador
#include <avr/io.h>
#include "serialPort.h"

 #define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

 //mensajes de bienvenida y despedida
 char msg1[] = "Hola Mundo, si presiona 's' termina el programa, por favor ingrese una tecla:\n\r";
 char msg2[] = "\n\rHasta luego!";

 int main(void)
 {
	 volatile char dato = 0;
	 
	 SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida

	 while(1)
	 {
		 SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
		 dato = SerialPort_Recive_Data();

		 // Si presionan 's' se termina el programa
		 if( dato == 's')
		 {
			 SerialPort_Send_String(msg2);  // Envío el string de despedida
			 while(1);
		 }
		 else
		 {	// Eco:
			 SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
			 SerialPort_Send_Data(dato);			  // Envío el dato recibido
		 }
	 }
	 return 0;
 }
*/
 /*
 //4- transmitir cadenas +  eco usando interrupción Rx
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "serialPort.h"

 #define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

 //mensajes de bienvenida y despedida
 char msg1[] = "Uso de interrup RXC, si presiona 's' termina el programa, por favor ingrese una tecla:\n\r";
 char msg2[] = "\n\rHasta luego!";

 //comunicación con la ISR
 volatile char RX_Buffer=0;

 int main(void)
 {
	 
	 SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	 SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	 SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	 SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida
	 SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
	 sei();								// Activo la mascara global de interrupciones (Bit I del SREG en 1)

	 while(1)
	 {
		 if(RX_Buffer){ // recepción NO Bloqueante
			 // Si presionan 's' se termina el programa
			 if(RX_Buffer == 's'){
				 SerialPort_Send_String(msg2);  // Envío el string de despedida
				 while(1);
			 }
			 else{	// Eco:
				 SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
				 SerialPort_Send_Data(RX_Buffer);			  // Envío el dato recibido
			 }
			 RX_Buffer=0;
		 }
		 //otra tarea
	 }
	 return 0;
 }

 // Rutina de Servicio de Interrupción de Byte Recibido
 ISR(USART_RX_vect){
	 RX_Buffer = UDR0; //la lectura del UDR borra flag RXC
 }

 */