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
#define F_CPU 16000000UL

// Colecci?n de m?sica RTTL
const char *rtttl_library[]=
{
	"Megalovania:d=16,o=5,b=200:d, d, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, c, c, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, b4, b4, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, a#4, a#4, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g",
	
	"AllStar:d=4,o=5,b=40:16g.,32d.6,32b.,16b.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,16g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16e.,d,32g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,32g.,32g.,16d.6,32b.,32b.,16a.,32g.,32g.,16a.,8e",
	
	"Argentina:d=4,o=6,b=80:8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g.5,8e5,c5,8e.5,16g5,f5,8f.5,16a5,g5,8a.5,16b5,c,8c.5"//,16c5,8c.5,16c5,8c.5,16d5,e5,8e.5,16e5,8e5,8g5,8f_.5"//,16a5,a5,g5,p,8g.5,16b5,a5,8a.5,16c,f_5,8f_.5,16a5,g5,p,8p,8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g5,8f5,8e5,c5,8e.5,16c,f5,8f.5,16a5,g5,8a.5,16b5,c",
	
	"BarbieGirl:d=4,o=5,b=125:32e,32f#,8g#,8e,8g#,8c#6,a,8p,16p,16g#,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,b,g#,e,c#4,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,8p,8c#6,8b,8c#6,8p,8c#6,8b,8c#6",

	"Doom:d=32,o=5,b=56:f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,e6,a#,a#,f6,f#6,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,8e6",
	
	"ImBlue:d=4,o=6,b=63:16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16a#,16c#,16f#,8g#,16b5,16f#,8g#,16f#,16g#,16a#,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#",
	
	"Tetris:d=4,o=6,b=80:8f7,16c7,16c#7,16d#7,32f7,32d#7,16c#7,16c7,8a#,16a#,16c#7,8f7,16d#7,16c#7,8c.7,16c#7,8d#7,8f7,8c#7,8a#,a#,8d#7,16f#7,8a#7,16g#7,16f#7,8f.7,16c#7,8f7,16d#7,16c#7,8c7,16c7,16c#7,8d#7,8f7,8c#7,8a#,8a#",
	
	"AmongUs:d=4,o=5,b=100:8c6,8d#6,8f6,8f#6,8f6,8d#6,8c6,4p,16a#5,16d6,16c6,16p,4p,8a#4,8c5,8p,8c6,8d#6,8f6,8f#6,8f6,8d#6,8f#6,4p,8p,12f#6,12f6,12d#6,12f#6,12f6,12d#6,8c5,8p"
};


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
int tocar(void);

#endif /* RINGTONE_H_ */