/*
 * EjemploTimerRingtone.c
 *
 * Created: 23/10/2020 08:26:59 p. m.
 * Autor:								Pereira F?bio (01/09/2008) - Para un microcontrolador Freescale HCS08
 * Autor migraci?n / modificaci?n:		Perri Victor
 * Asignatura:							Dise?o de Controladores Digitales
-----------------------------------------------------------*/

#include "ringtone.h"
#include <avr/pgmspace.h>  // Libreria para guardar en ROM
#include <avr/io.h>        // Required library for ATmega328P


// Define your welcome message and song list
const char PROGMEM bienvenida[] = "Willkommen!";
const char PROGMEM *songNames[] = {"1-Megalovania", "2-Smash Mouth", "3-Himno Argentino", "4-I'm a Barbie Girl", "5-Doom Theme", "6-I'm Blue", "7-Tetris Theme", "8-Among Us Theme"};
// Colecci?n de m?sica RTTL
const char PROGMEM *songList[] = {
	"Megalovania:d=16,o=5,b=200:d, d, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, c, c, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, b4, b4, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g, a#4, a#4, d6, p, a, 8p, g#, p, g, p, f, p, d, f, g",
	
	"AllStar:d=4,o=5,b=40:16g.,32d.6,32b.,16b.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,16g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16e.,d,32g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,32g.,32g.,16d.6,32b.,32b.,16a.,32g.,32g.,16a.,8e",
	
	"Argentina:d=4,o=6,b=80:8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g.5,8e5,c5,8e.5,16g5,f5,8f.5,16a5,g5,8a.5,16b5,c,8c.5,16c5,8c.5,16c5,8c.5,16d5,e5,8e.5,16e5,8e5,8g5,8f_.5,16a5,a5,g5,p,8g.5,16b5,a5,8a.5,16c,f_5,8f_.5,16a5,g5,p,8p,8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g5,8f5,8e5,c5,8e.5,16c,f5,8f.5,16a5,g5,8a.5,16b5,c",
	
	"BarbieGirl:d=4,o=5,b=125:32e,32f#,8g#,8e,8g#,8c#6,a,8p,16p,16g#,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,b,g#,e,c#4,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,8p,8c#6,8b,8c#6,8p,8c#6,8b,8c#6",

	"Doom:d=32,o=5,b=56:f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,e6,a#,a#,f6,f#6,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,8e6",
	
	"ImBlue:d=4,o=6,b=63:16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16a#,16c#,16f#,8g#,16b5,16f#,8g#,16f#,16g#,16a#,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#",
	
	"Tetris:d=4,o=6,b=80:8f7,16c7,16c#7,16d#7,32f7,32d#7,16c#7,16c7,8a#,16a#,16c#7,8f7,16d#7,16c#7,8c.7,16c#7,8d#7,8f7,8c#7,8a#,a#,8d#7,16f#7,8a#7,16g#7,16f#7,8f.7,16c#7,8f7,16d#7,16c#7,8c7,16c7,16c#7,8d#7,8f7,8c#7,8a#,8a#",
	
	"AmongUs:d=4,o=5,b=100:8c6,8d#6,8f6,8f#6,8f6,8d#6,8c6,4p,16a#5,16d6,16c6,16p,4p,8a#4,8c5,8p,8c6,8d#6,8f6,8f#6,8f6,8d#6,8f#6,4p,8p,12f#6,12f6,12d#6,12f#6,12f6,12d#6,8c5,8p"
};

unsigned char duration,octave;
unsigned int tempo;

// Saco el sonido por el PIN5 del PORTD: freq en Hz,dur en ms
void sound(unsigned int freq,unsigned int dur)
{
	while (sound_playing);      // Si hay alg?n sonido presente,espero a que termine
	
	duration_timer = dur;       // Seteo el tiempo de duraci?n
	
	// Activo la salida y configuro el timer para que genere la se?al de la frecuencia apropiada
	TCCR1A|=(1<<COM1A0);
	
	// Actualizo el valor de OCR1A para que produzca la nota adecuada
	OCR1A=(8000000/(freq))-1;
	
	sound_playing = 1;          // Activo el flag para avisar que hay una nota sonando
}

// Esta funci?n reproduce una canci?n que se le pase en un string con formato RTTTL
void play_song(char *song)
{
	unsigned char temp_duration,temp_octave,current_note,dot_flag;
	unsigned int calc_duration;
	duration = 4;                 // Duraci?n est?ndar = 4/4 = 1 beat
	tempo = 63;                   // Tempo est?ndar = 63 bpm
	octave = 6;                   // Octava est?ndar = 6th
	while (*song != ':') song++;  // Busca el primer ':'
	song++;                       // Saltea el primer ':'
	while (*song!=':')            // Repite hasta encontrar ':'
	{
		if (*song == 'd')           // Entra si es el seteo de la duraci?n
		{
			duration = 0;             // Seteo la duraci?n en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Si el caracter es un n?mero,seteo la duraci?n
			if (*song>='0' && *song<='9') duration = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			// Me fijo si el caracter es un n?mero,ya que la diraci?n puede ser de dos d?gitos de largo
			if (*song>='0' && *song<='9')
			{ // Multiplico duraci?n por 10 y le agrego el valor del caracter
				duration = duration*10 + (*song - '0');
				song++;                 // Avanzo al pr?ximo caracter
			}
			while (*song == ',') song++;  // Salteo ','
		}
		
		if (*song == 'o')           // Entra si es el seteo de la octava
		{
			octave = 0;               // Seteo la octava en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Si el caracter es un n?mero,seteo la octava
			if (*song>='0' && *song<='9') octave = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == ',') song++;  // Salteo ','
		}
		if (*song == 'b')           // Entra si es el seteo del tempo (beats por minuto)
		{
			tempo = 0;                // Seteo el tempo en cero (temporalmente)
			song++;                   // Avanzo al pr?ximo caracter
			while (*song == '=') song++;  // Salteo '='
			while (*song == ' ') song++;  // Salteo los espacios
			// Ahora leo el seteo del tempo (puede tener 3 d?gitos de largo)
			if (*song>='0' && *song<='9') tempo = *song - '0';
			song++;                   // Avanzo al pr?ximo caracter
			if (*song>='0' && *song<='9')
			{
				tempo = tempo*10 + (*song - '0'); // El tempo tiene dos d?gitos
				song++;                 // Avanzo al pr?ximo caracter
				if (*song>='0' && *song<='9')
				{
					tempo = tempo*10 + (*song - '0'); // El tempo tiene tres d?gitos
					song++;               // Avanzo al pr?ximo caracter
				}
			}
			while (*song == ',') song++;  // Salteo ','
		}
		while (*song == ',') song++;    // Salteo ','
	}
	song++;                       // Avanzo al pr?ximo caracter
	// read the musical notes
	while (*song)                 // Repito hasta que el caracter sea null
	{
		current_note = 255;         // Nota por defecto = pausa
		temp_octave = octave;       // Seteo la octava a la por defecto de la canci?n
		temp_duration = duration;   // Seteo la duraci?n a la por defecto de la canci?n
		dot_flag = 0;               // Borro el flag de detecci?n de punto
		// Busco un prefijo de duraci?n
		if (*song>='0' && *song<='9')
		{
			temp_duration = *song - '0';
			song++;
			if (*song>='0' && *song<='9')
			{
				temp_duration = temp_duration*10 + (*song - '0');
				song++;
			}
		}
		// Busco una nota
		switch (*song)
		{
			case 'c': current_note = 0; break;    // C (do)
			case 'd': current_note = 2; break;    // D (re)
			case 'e': current_note = 4; break;    // E (mi)
			case 'f': current_note = 5; break;    // F (fa)
			case 'g': current_note = 7; break;    // G (sol)
			case 'a': current_note = 9; break;    // A (la)
			case 'b': current_note = 11; break;   // B (si)
			case 'p': current_note = 255; break;  // pausa
		}
		song++;                     // Avanzo al pr?ximo caracter
		// Busco un '#' siguiendo la nota
		if (*song=='#')
		{
			current_note++;   // Incremento la nota (A->A#,C->C#,D->D#,F->F#,G->G#)
			song++;                   // Avanzo al pr?ximo caracter
		}




		// Busco '.' (extiende la duraci?n de la nota un 50%)
		if (*song=='.')
		{
			dot_flag = 1;             // Si se encuentra '.',seteo el flag
			song++;                   // Avanzo al pr?ximo caracter
		}
		// Busco un sufijo de una octava
		if (*song>='0' && *song<='9')
		{
			temp_octave = *song - '0';// Seteo la octava en consecuencia
			song++;                   // Avanzo al pr?ximo caracter
		}
		if (*song=='.') // Un punto puede ser encontrado incluso despu?s de una octava
		{
			dot_flag = 1;             // Si se encuentra '.',seteo el flag
			song++;                   // Avanzo al pr?ximo caracter
		}
		while (*song == ',') song++;    // Salteo ','
		// Calculo la duraci?n de la nota
		calc_duration = (60000/tempo)/(temp_duration);
		calc_duration *= 4;         // La nota completa tiene cuatro beats
		// Chequeo si el flag de punto est? activado,de ser as?,extiendo la duraci?n en un 50%
		if (dot_flag) calc_duration = (calc_duration*3)/2;
		// Si la nota actual NO es una pausa,reproduzco la nota usando la funci?n sound
		if (current_note<255) sound(note[temp_octave-4][current_note],calc_duration);
		else
		{ // Si la nota actual es una pausa (255),espero dicha cantidad de tiempo
			duration_timer = calc_duration;
			sound_playing = 1;
		}
		while (sound_playing);      // Espero a la que nota/pausa en curso finalice
	}
}

void printSongList() {
	UART_Write_String_To_Buffer("Número de canciones almacenadas: ");
	UART_Write_Char_To_Buffer(MAX_SONGS);
	UART_Write_String_To_Buffer("Lista de canciones:\n");
	for (int i = 0; i < MAX_SONGS; i++) {
		UART_Write_String_To_Buffer(pgm_read_word(&songNames[i]));
	}
}