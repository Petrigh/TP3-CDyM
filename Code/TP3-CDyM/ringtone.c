/*
 * EjemploTimerRingtone.c
 *
 * Created: 23/10/2020 08:26:59 p. m.
 * Autor:								Pereira F?bio (01/09/2008) - Para un microcontrolador Freescale HCS08
 * Autor migraci?n / modificaci?n:		Perri Victor
 * Asignatura:							Dise?o de Controladores Digitales
-----------------------------------------------------------*/

#include "ringtone.h"
#include "timer.h"

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


int tocar(char song_sel)
{
		for (song_sel=0;song_sel<11;song_sel++)
		{
			play_song(rtttl_library[song_sel]); // Reproduzco la canci?n
			// Espero dos segundos antes de comenzar la siguiente canci?n
			duration_timer = 2000;
			sound_playing = 1;
			while (sound_playing);
		}

	return 0; // Nunca va a alcanzar esta parte
}