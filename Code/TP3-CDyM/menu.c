/*
 * menu.c
 *
 * Created: 11/6/2023 13:21:50
 *  Author: Infinio
 */ 
#include "menu.h"

void menuInit(void){
	uint8_t idCancion = 1;
	bool mostrarBienvenida = false;
	
	const char PROGMEM menu[6][50] = {
		"\nOpciones disponibles:\n",
		"1. PLAY: Reproducir canción\n",
		"2. STOP: Detener reproducción\n",
		"3. NUM: Seleccionar número de canción\n",
		"4. RESET: Reiniciar sistema\n",
		"Ingrese el número de opción: "
	};
	
	
	const char PROGMEM menuSwitch[5][50] = {
		"Reproduciendo ",
		"Reproduccion detenida\n",
		"Ingrese el número de canción a seleccionar: ",
		"Reiniciando el sistema...\n",
		"Comando no válido\n"
	};
}
void MENU_Update(void){

	if (!mostrarBienvenida) {
		printSongList();
		mostrarBienvenida = true;
	}

	UART_Write_String_To_Buffer(pgm_read_word(&menu[0]));
	UART_Write_String_To_Buffer(pgm_read_word(&menu[1]));
	UART_Write_String_To_Buffer(pgm_read_word(&menu[2]));
	UART_Write_String_To_Buffer(pgm_read_word(&menu[3]));
	UART_Write_String_To_Buffer(pgm_read_word(&menu[4]));
	UART_Write_String_To_Buffer(pgm_read_word(&menu[5]));
	while (!UART_Get_Char_From_Buffer(opcion));

	switch (*opcion) {
		case 1: {
			UART_Write_String_To_Buffer(pgm_read_word(&menuSwitch[0]));
			play_song(pgm_read_word(&songList[idCancion - 1]));
			break;
		}
		case 2: {
			UART_Write_String_To_Buffer(pgm_read_word(&menuSwitch[1]));
			break;
		}
		case 3: {
			UART_Write_String_To_Buffer(pgm_read_word(&menuSwitch[2]));
			while (!UART_Get_Char_From_Buffer(opcion));
			break;
		}
		case 4: {
			printf_P(pgm_read_word(&menuSwitch[3]));
			mostrarBienvenida = false;
			idCancion = 0;
			break;
		}
		default:
		printf_P(pgm_read_word(&menuSwitch[4]));
		break;
	}	
}
