#define F_CPU 16000000UL		// 16 MHz

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/pgmspace.h"
#include "serialPort.h"
#include "ringtones.h"
#include "menu.h"

//Menu
const char PROGMEM menu[] = "\n\nOpciones disponibles:\n PLAY: Reproducir canción\n STOP: Detener reproducción\n NUM: Seleccionar número de canción\n RESET: Reiniciar sistema\nIngrese el número de opción: \n ";
//Feedback
const char PROGMEM menuSwitch1[] = "Reproduciendo\n ";
const char PROGMEM menuSwitch2[] = "Reproduccion detenida\n ";
const char PROGMEM menuSwitch3[] = "Ingrese el número de canción a seleccionar: ";
const char PROGMEM menuSwitch4[] = "Reiniciando el sistema...\n";
const char PROGMEM menuSwitch5[] = "Comando no válido\n ";
const char PROGMEM menuSwitch6[] = "Cargando\n ";
// Mensaje de bienvenida
const char PROGMEM bienvenida[] = "Willkommen!\n";

int i = 0;

char c;
int num;


void printBienvenida() {
	//Envia mensaje de bienvenida desde ROM
	int i = 0;
	char c;
	SerialPort_Wait_For_TX_Buffer_Free();
	c = pgm_read_byte(bienvenida + i);
	while(c != '\0'){
		SerialPort_Send_Data(c);
		i++;
		c = pgm_read_byte(bienvenida + i);
		SerialPort_Wait_For_TX_Buffer_Free();
	}
	//Muestra la cantidad de canciones
	SerialPort_Send_String("Número de canciones almacenadas: ");
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('0' + CANCIONES);
	SerialPort_Wait_For_TX_Buffer_Free();
	SerialPort_Send_Data('\n');
}


void printMenu(){
	//Muestra Menu en consola desde ROM
	c = pgm_read_byte(menu + i);
	SerialPort_Wait_For_TX_Buffer_Free();
	while(c != '\0'){
		SerialPort_Send_Data(c);
		i++;
		c = pgm_read_byte(menu + i);
		SerialPort_Wait_For_TX_Buffer_Free();
	}
}

void opcionMenu(char opcion){
	switch(opcion){
		case 'p':		
			if (menuFlag != CARGANDO)
			{
				lectorCancion = 0;
				i= 0;
				c = pgm_read_byte(menuSwitch6 + i);
				while(c != '\0'){
					SerialPort_Send_Data(c);
					i++;
					c = pgm_read_byte(menuSwitch6 + i);
					SerialPort_Wait_For_TX_Buffer_Free();
				}
				menuFlag = CARGANDO;
				eleccionMenu(theme);
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
			menuFlag = STOP;
		break;
		case 'n':
			free(cancionRAM);
			printSongList();
			i= 0;
			c = pgm_read_byte(menuSwitch3 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch3 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
			menuFlag=SELECCIONANDO;
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
			menuFlag=RESET;
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

void menuMef(){
	switch (menuFlag){
		case REPRODUCIR:
			i= 0;
			c = pgm_read_byte(menuSwitch1 + i);
			while(c != '\0'){
				SerialPort_Send_Data(c);
				i++;
				c = pgm_read_byte(menuSwitch1 + i);
				SerialPort_Wait_For_TX_Buffer_Free();
			}
			menuFlag = REPRODUCIENDO;
		break;
		case REPRODUCIENDO:
			play_song();
		break;
		case CARGANDO:
			play_song();
		break;
		case STOP:
			mostrarMenu=1;
			menuFlag = SILENCIO;
		break;
		case SELECCIONANDO:	
			if(RX_Buffer_flag){ // recepción NO Bloqueante
				if(!RX_Buffer_overflow_flag){
					SerialPort_Send_String(RX_Buffer);
					if(RX_Buffer[1]=='\r'){
						if(RX_Buffer[0]<'1' || RX_Buffer[0]>'0'+CANCIONES){
							SerialPort_Send_String("\nCancion invalida\n");
						}else{
							theme=RX_Buffer[0];
							mostrarMenu=1;
							menuFlag = SILENCIO;
						}
					}
					RX_Buffer_flag=0;
				}else{
					RX_Buffer_overflow_flag=0;
					RX_Buffer_flag=0;
					SerialPort_Send_String("\nCancion invalida\n");
				}
				SerialPort_Wait_For_TX_Buffer_Free();
			}
		break;
		case SILENCIO:
			mostrarMenu=0;
			mostrarBienvenida=0;
		break;
		case RESET:
			_delay_ms(500);
			wdt_enable(WDTO_15MS);
		break;
	}
}