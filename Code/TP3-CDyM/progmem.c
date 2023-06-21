/*
 * PruebaPROGMEM.c
 *
 * Created: 13/06/2023 10:22:30
 * Author : J.J.
 */ 

#include <avr/io.h>
#include "avr/pgmspace.h"

/*

//EJEMPLO 4: optimizaci?n del uso de RAM utilizando directiva PROGMEM y biblioteca pgmspace  



const char PROGMEM rtttl_library1[]="TheSimpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char PROGMEM rtttl_library2[]="MissionImp:d=4,o=6,b=150:16d5,16d#5,16d5,16d#5,16d5,16d#5,16d5,16d5,16d#5,16e5,16f5,16f#5,16g5,8g5,4p,8g5,4p,8a#5,8p,8c6,8p,8g5,4p,8g5,4p,8f5,8p,8p,8g5,4p,4p,8a#5,8p,8c6,8p,8g5,4p,4p,8f5,8p,8f#5,8p,8a#5,8g5,1d5";
const char PROGMEM rtttl_library3[]="Batman:d=8,o=5,b=160:16a,16g#,16g,16f#,16f,16f#,16g,16g#,4a.,p,d,d,c#,c#,c,c,c#,c#,d,d,c#,c#,c,c,c#,c#,d,d,c#,c#,c,c,c#,c#,g6,p,4g6";

const char * rtttl_library[]=
{
	rtttl_library1,
	rtttl_library2,
	rtttl_library3
};

void play_song(char *song)
{
	char c;
	c=pgm_read_byte(song);
	while (c != '\0'){
		PORTD=c;
		song++;
		c=pgm_read_byte(song);
	}
}

int main(void)
{
	unsigned char song_sel;
	DDRD=0xFF;
	while(1)
	{
/ *
		play_song(rtttl_library1);
		play_song(rtttl_library2);
		play_song(rtttl_library3);* /

		for (song_sel=0;song_sel<3;song_sel++)
		{
			play_song(rtttl_library[song_sel]);

		}
	}
	return 0;
}*/

/*
//EJEMPLO 2: constante cadena de caracteres con directiva PROGMEM
// Se guarda en flash, no consume RAM, pero require de mecanismo especial 
// para leerla (funicones de biblioteca pgmspace)

const char PROGMEM texto[]="HOLA MUNDO!\r\n";

int main(void)
{
	DDRD=0xFF;
	uint8_t i=0;
	char c;
	while (1)
	{
		c=pgm_read_byte(&texto[i]);
		while( c!='\0'){
			PORTD= c;
			i++;
			c=pgm_read_byte(&texto[i]);
		}
		i=0;
	}
}*/
