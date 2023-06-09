
//#include "main.h"
#include "main.h"
#include "uart.h"
#include "timer.h"
#include "ringtone.h"

int main(void)
{
	// Declaraciones de variables
	
	unsigned char song_sel;
	
	//Inicializo Timer0 y Timer1
	TimerInit();

	//Inicializo UART (hacerlo xd)
	UART_Init();
	//Habilito la m?scara de interrupciones
	
	sei();
	
	while(1)
	{
		//Main
		//Eleccion de opcion
		tocar(song_sel);
	}

	return 0; // Nunca va a alcanzar esta parte
}