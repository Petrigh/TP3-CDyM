#ifndef MAIN_H_
#define MAIN_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <avr/io.h>
#include "avr/interrupt.h"
#define F_CPU 16000000UL

const char menu[][50] PROGMEM = {
	"\nOpciones disponibles:\n",
	"1. PLAY: Reproducir canci�n\n",
	"2. STOP: Detener reproducci�n\n",
	"3. NUM: Seleccionar n�mero de canci�n\n",
	"4. RESET: Reiniciar sistema\n",
	"Ingrese el n�mero de opci�n: "
};

const char menuSwitch[][50] PROGMEM = {
	"Reproduciendo ",
	"Reproduccion detenida\n",
	"Ingrese el n�mero de canci�n a seleccionar: ",
	"Reiniciando el sistema...\n",
	"Comando no v�lido\n"
};

#endif /* MAIN_H_ */
