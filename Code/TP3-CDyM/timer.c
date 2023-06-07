/*
 * timer.c
 *
 * Created: 5/6/2023 15:15:20
 *  Author: Infinio
 */ 
#include "timer.h"

void TimerInit(void){
		
		// ------------------------ Timer 0 ------------------------
		
		// Configuro una interrupci?n cada 1 mseg
		OCR0A = 248;			//124 para 8MHz y 248 para 16MHz
		TCCR0A = (1<<WGM01);   // Modo CTC,clock interno,prescalador 64
		TCCR0B = (1<<CS01)|(1<<CS00);   // Modo CTC,clock interno,prescalador 64
		TIMSK0 = (1<<OCIE0A);   // Habilito Timer 0 en modo de interrupci?n de comparaci?n
		
		
		// ------------------------ Timer 1 ------------------------
		
		TCCR1A|=(1<<COM1A0);// Configuro Timer1 para clk con prescaler P=1,modo CTC y salida por pin
		TCCR1B|=(1<<WGM12)|(1<<CS10);
		DDRB|=(1<<PINB1); // El PIN1 del PORTB ser? el pin de salida

}


// Control de la duraci?n del sonido
ISR (TIMER0_COMPA_vect) // ISR para la interrupci?n de comparaci?n del Timer 0
{
	if (duration_timer) duration_timer--; // Decremento el timer si > 0
	else                                  // si timer es = 0
	{
		TCCR1A=0;	// Desactivo el timer 1
		sound_playing = 0;                  // Borro el flag para avisar que no hay una nota sonando
	}
}
