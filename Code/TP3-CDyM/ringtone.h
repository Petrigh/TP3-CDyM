/*
 * ringtone.h
 *
 * Created: 5/6/2023 14:49:41
 *  Author: Infinio
 */ 


#ifndef RINGTONE_H_
#define RINGTONE_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <avr/io.h>
#include "avr/interrupt.h"
#include <avr/pgmspace.h>
#include "timer.h"
#include "uart.h"

#define F_CPU 16000000UL
#define MAX_SONGS 8

const char PROGMEM bienvenida[];
const char PROGMEM songNames[MAX_SONGS][20];
const char PROGMEM songList[MAX_SONGS][200];

void sound(unsigned int, unsigned int);
void play_song(char*);
int tocar(char);

#endif /* RINGTONE_H_ */