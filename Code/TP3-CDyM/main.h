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
	"1. PLAY: Reproducir canción\n",
	"2. STOP: Detener reproducción\n",
	"3. NUM: Seleccionar número de canción\n",
	"4. RESET: Reiniciar sistema\n",
	"Ingrese el número de opción: "
};

const char menuSwitch[][50] PROGMEM = {
	"Reproduciendo ",
	"Reproduccion detenida\n",
	"Ingrese el número de canción a seleccionar: ",
	"Reiniciando el sistema...\n",
	"Comando no válido\n"
};

#endif /* MAIN_H_ */
