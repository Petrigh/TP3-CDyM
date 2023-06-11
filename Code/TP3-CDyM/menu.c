/*
 * menu.c
 *
 * Created: 11/6/2023 13:21:50
 *  Author: Infinio
 */ 
#include "menu.h"

PGM_P menuPtr;
PGM_P menuSwitchPtr;
PGM_P songPtr;

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
	
	memcpy_P(&menuPtr, &menu[0], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	memcpy_P(&menuPtr, &menu[1], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	memcpy_P(&menuPtr, &menu[2], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	memcpy_P(&menuPtr, &menu[3], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	memcpy_P(&menuPtr, &menu[4], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	memcpy_P(&menuPtr, &menu[5], sizeof(PGM_P));
	UART_Write_String_To_Buffer(menuPtr);
	while (!UART_Get_Char_From_Buffer(opcion));

	switch (*opcion) {
		case 1: {
			memcpy_P(&menuSwitchPtr, &menuSwitch[0], sizeof(PGM_P));
			UART_Write_String_To_Buffer(menuSwitchPtr);
			memcpy_P(&songPtr, &songList[idCancion-1], sizeof(PGM_P));
			play_song(songPtr);
			break;
		}
		case 2: {
			memcpy_P(&menuSwitchPtr, &menuSwitch[1], sizeof(PGM_P));
			UART_Write_String_To_Buffer(menuSwitchPtr);
			break;
		}
		case 3: {
			memcpy_P(&menuSwitchPtr, &menuSwitch[2], sizeof(PGM_P));
			UART_Write_String_To_Buffer(menuSwitchPtr);
			while (!UART_Get_Char_From_Buffer(opcion));
			break;
		}
		case 4: {
			memcpy_P(&menuSwitchPtr, &menuSwitch[3], sizeof(PGM_P));
			UART_Write_String_To_Buffer(menuSwitchPtr);
			mostrarBienvenida = false;
			idCancion = 0;
			break;
		}
		default:
		memcpy_P(&menuSwitchPtr, &menuSwitch[4], sizeof(PGM_P));
		UART_Write_String_To_Buffer(menuSwitchPtr);
		break;
	}	
}
