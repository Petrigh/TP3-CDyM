#define F_CPU 16000000UL		// 16 MHz

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/pgmspace.h"
#include "serialPort.h"
#include "ringtones.h"
#include "menu.h"

//Menu
const char PROGMEM menu[] = "\nOpciones disponibles:\np. PLAY: Reproducir canci�n\ns. STOP: Detener reproducci�n\nn. NUM: Seleccionar n�mero de canci�n\nr. RESET: Reiniciar sistema\nIngrese el n�mero de opci�n: \n";
//Feedback
const char PROGMEM menuSwitch1[] = "Reproduciendo\n";
const char PROGMEM menuSwitch2[] = "Reproduccion detenida\n";
const char PROGMEM menuSwitch3[] = "Ingrese el n�mero de canci�n a seleccionar: \n";
const char PROGMEM menuSwitch4[] = "Reiniciando el sistema...\n";
const char PROGMEM menuSwitch5[] = "Comando no v�lido\n";
// Mensaje de bienvenida
const char PROGMEM bienvenida[] = "Willkommen!\n";


void printBienvenida() {
	//Envia mensaje de bienvenida desde ROM
	int i = 0;
	char c;
	c = pgm_read_byte(bienvenida + i);
	while(c != '\0'){
		SerialPort_Send_Data(c);
		i++;
		c = pgm_read_byte(bienvenida + i);
		SerialPort_Wait_For_TX_Buffer_Free();
	}
	//Muestra la cantidad de canciones
	SerialPort_Send_String("N�mero de canciones almacenadas: ");
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0' + CANCIONES);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('\n');
}


void printMenu(){
	//Muestra Menu en consola desde ROM
	int i = 0;
	char c;
	c = pgm_read_byte(menu + i);
	while(c != '\0'){
		SerialPort_Send_Data(c);
		i++;
		c = pgm_read_byte(menu + i);
		SerialPort_Wait_For_TX_Buffer_Free();
	}
}

void opcionMenu(char opcion){
	int i;	char c;
	switch(opcion){
		case 'p':
			if (!sound_playing)
			{
				i= 0;
				c = pgm_read_byte(menuSwitch1 + i);
				while(c != '\0'){
					SerialPort_Send_Data(c);
					i++;
					c = pgm_read_byte(menuSwitch1 + i);
					SerialPort_Wait_For_TX_Buffer_Free();
				}
				eleccionMenu(theme);
				
				SerialPort_Send_String("\n\n\n\n\n ");
				mostrarMenu=1;
			}
		break;
		
		case 's':
			i= 0;
			c = pgm_read_byte(menuSwitch2 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch2 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
			
			mostrarMenu=1;
		break;
		
		case 'n':
			SerialPort_Send_String("\n\n\n\n\n ");
			printSongList();
			i= 0;
			c = pgm_read_byte(menuSwitch3 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch3 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
			SerialPort_Wait_Until_New_Data();
			theme=RX_Buffer;
			while(theme<='1' || theme>=('0'+CANCIONES)){
				if(theme<='1' || theme>=('0'+CANCIONES)){
					SerialPort_Send_String("\nCancion invalida\n");					
				}
				SerialPort_Wait_Until_New_Data();
				theme=RX_Buffer;
			}
			mostrarMenu=1;
			UDR0=0;
			SerialPort_Send_String("\n\n\n\n\n\n\n\n\n\n\n\n ");
		break;
		
		case 'r':
			sound_playing = 0;
			i= 0;
			c = pgm_read_byte(menuSwitch4 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch4 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
			theme='1';
			mostrarBienvenida=1;
			mostrarMenu=1;
			_delay_ms(3000);		
			SerialPort_Send_String("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n ");
		break;
		
		default:
			i= 0;
			c = pgm_read_byte(menuSwitch5 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch5 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
		break;
	}
	
}