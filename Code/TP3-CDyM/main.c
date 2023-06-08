
//#include "main.h"
#include "main.h"
#include "serialPort.h"
#include "timer.h"
#include "ringtone.h"

int main(void)
{
	// Declaraciones de variables
	bool mostrarBienvenida = false;
	uint8_t opcion;
	uint8_t idCancion = 0;
	ringtonesInit(); //Este guarda las cosas en ROM
	
	//Inicializo Timer0 y Timer1
	TimerInit();

	//Inicializo UART
	SerialPort_Init();
	
	//Habilito la m?scara de interrupciones
	sei();

	while (true) {
		if (!mostrarBienvenida) {
			printSongList();
			mostrarBienvenida = true;
		}

		printf("\nOpciones disponibles:\n");
		printf("1. PLAY: Reproducir canción\n");
		printf("2. STOP: Detener reproducción\n");
		printf("3. NUM: Seleccionar número de canción\n");
		printf("4. RESET: Reiniciar sistema\n");
		printf("Ingrese el número de opción: ");
		scanf("%d", &opcion);

		switch (opcion) {
			case 1: {
				play_song(pgm_read_word(&songList[idCancion]));
				break;
			}
			case 2: {
				printf("Reproducción detenida\n");
				break;
			}
			case 3: {
				int songIndex;
				printf("Ingrese el número de canción a seleccionar: ");
				scanf("%d", &idCancion);
				break;
			}
			case 4: {
				printf("Reiniciando el sistema...\n");
				mostrarBienvenida = false;
				idCancion=0;
				break;
			}
			default:
			printf("Comando no válido\n");
			break;
		}
	}
	return 0;
}