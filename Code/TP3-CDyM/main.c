<<<<<<< HEAD

//#include "main.h"
#include "main.h"
#include "uart.h"
#include "timer.h"
#include "ringtone.h"
#include "seos.h"

=======
>>>>>>> c969e43a6451f4bfccf76fb79adcc66920ae6765
int main(void)
{
	// Declaraciones de variables
	bool mostrarBienvenida = false;
	uint8_t idCancion = 1;
	char *opcion;
	ringtonesInit(); //Este guarda las cosas en ROM
	
	// Inicializo Timer0 y Timer1
	TimerInit();

	// Inicializo UART
	UART_Init();
	
	// Habilito la m�scara de interrupciones
	sei();

	while (true) {

		
		//SEOS_Dispatch_Tasks();
		
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
				play_song(pgm_read_word(&songList[idCancion - 1]));
				break;
			}
			case 2: {
				UART_Write_String_To_Buffer(pgm_read_word(&menuSwitch[1]));
				break;
			}
			case 3: {
				int songIndex;
				printf_P(pgm_read_word(&menuSwitch[1]));
				while (!UART_Get_Char_From_Buffer(opcion));
				break;
			}
			case 4: {
				printf_P(pgm_read_word(&menuSwitch[1]));
				mostrarBienvenida = false;
				idCancion = 0;
				break;
			}
			default:
			printf_P(pgm_read_word(&menuSwitch[1]));
			break;
		} */
	}

	return 0;
}
