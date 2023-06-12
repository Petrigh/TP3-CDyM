/*
 * menu.c
 *
 * Created: 11/6/2023 13:21:50
 *  Author: Infinio
 */ 
#include "menu.h"


const char PROGMEM menu[6][39] = {
	"--------------OPCIONES---------------\n",
	"1. PLAY: Reproducir canción          \n",
	"2. STOP: Detener reproducción        \n",
	"3. NUM: Seleccionar número de canción\n",
	"4. RESET: Reiniciar sistema          \n",
	"Ingrese el número de opción:         \n"
};
void menuInit(void){
	uint8_t idCancion = 1;
	bool mostrarBienvenida = false;
	//const char PROGMEM menu[29] = "1. PLAY: Reproducir canción\n";
	/*
	const char PROGMEM menu[6][50] = {
		"\nOpciones disponibles:\n",
		"1. PLAY: Reproducir canción\n",
		"2. STOP: Detener reproducción\n",
		"3. NUM: Seleccionar número de canción\n",
		"4. RESET: Reiniciar sistema\n",
		"Ingrese el número de opción: "
	};
	*/
	/*
	const char PROGMEM menuSwitch[5][50] = {
		"Reproduciendo ",
		"Reproduccion detenida\n",
		"Ingrese el número de canción a seleccionar: ",
		"Reiniciando el sistema...\n",
		"Comando no válido\n"
	};
	*/
}
void MENU_Update(void){

	if (!mostrarBienvenida) {
		printSongList();
		mostrarBienvenida = true;
	}
	SerialPort_TX_Interrupt_Enable();
	for(uint8_t j=0;j<5;j++)
		for(uint8_t i=0;i<37;i++)
			UART_Write_Char_To_Buffer(pgm_read_byte(&menu[j][i]));
	/*
	UART_Write_String_To_Buffer(pgm_read_byte(&menu[1]));
	UART_Write_String_To_Buffer(pgm_read_byte(&menu[2]));
	UART_Write_String_To_Buffer(pgm_read_byte(&menu[3]));
	UART_Write_String_To_Buffer(pgm_read_byte(&menu[4]));
	UART_Write_String_To_Buffer(pgm_read_byte(&menu[5]));
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
	*/
}
