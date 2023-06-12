
//#include "main.h"
#include "main.h"

int main(void)
{
	// Declaraciones de variables
	

	// Inicializo UART
	UART_Init();
	// Inicializo Timer0 y Timer1
	TimerInit();
	
	// Inicializo el Menu
	menuInit();
	// Habilito la m�scara de interrupciones
	sei();

	while (true) {

		SEOS_Dispatch_Tasks();
		
	}

	return 0;
}
