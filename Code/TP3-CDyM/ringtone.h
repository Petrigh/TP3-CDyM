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
#include "timer.h"
#define F_CPU 16000000UL
#define MAX_SONGS 8

// La siguiente matriz almacena las frecuencias de las notas musicales
const unsigned int note[4][12] =
{   // C    C#    D     D#    E     F     F#    G     G#    A     A#    B
	{262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494},// 4ta octava
	{523, 554, 587, 622, 659, 698, 740, 784, 830, 880, 932, 988},// 5ta octava
	{1047,1109,1175,1244,1319,1397,1480,1568,1660,1760,1865,1976},// 6ta octava
	{2093,2218,2349,2489,2637,2794,2960,3136,3320,3520,3728,3951}  // 7ma octava
};

void sound(unsigned int, unsigned int);
void play_song(char*);
int tocar(char);

#endif /* RINGTONE_H_ */