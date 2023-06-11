/*
 * menu.h
 *
 * Created: 11/6/2023 13:22:01
 *  Author: Infinio
 */ 


#ifndef MENU_H_
#define MENU_H_


#include <stdbool.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr/interrupt.h"
#include "ringtone.h"


bool mostrarBienvenida;
uint8_t idCancion;
char *opcion;

const char PROGMEM menu[6][50];

const char PROGMEM menuSwitch[5][50];


#endif /* MENU_H_ */