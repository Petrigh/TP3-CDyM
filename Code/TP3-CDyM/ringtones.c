//#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/pgmspace.h"
#include "serialPort.h"
#include "ringtones.h"
#include "menu.h"

//Lista de nombres de las canciones
                 // el espacio antes del 1 es porque se lo come el buffer
const char PROGMEM rtttlSongNames[] = {" 1. Megalovania\n 2. AllStar\n 3. Argentina\n 4. Barbie Girl\n 5. Doom Theme\n 6. I'm Blue\n 7. Tetris Theme\n 8. Among Us Theme\n "};
// Colecci?n de m?sica RTTL
const char PROGMEM rtttl_library1[]="Megalovania:d=16,o=5,b=120:d,d,d6,p,a,8p,g#,p,g,p,f,p,d,f,g,c,c,d6,p,a,8p,g#,p,g,p,f,p,d,f,g,b4,b4,d6,p,a,8p,g#,p,g,p,f,p,d,f,g,a#4,a#4,d6p,a,8p,g#,p,g,p,f,p,d,f,g";
const char PROGMEM rtttl_library2[]="AllStar:d=4,o=5,b=40:16g.,32d.6,32b.,16b.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,16g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16e.,d,32g.,32g.,32d.6,32b.,32b.,32a.,32a.,32g.,32g.,16c.6,32b.,32b.,32a.,32a.,32g.,32g.,16d.6,32b.,32b.,16a.,32g.,32g.,16a.,8e";
const char PROGMEM rtttl_library3[]="Argentina:d=4,o=6,b=80:8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g.5,8e5,c5,8e.5,16g5,f5,8f.5,16a5,g5,8a.5,16b5,c,8c.5,16c5,8c.5,16c5,8c.5,16d5,e5,8e.5,16e5,8e5,8g5,8f_.5,16a5,a5,g5,p,8g.5,16b5,a5,8a.5,16c,f_5,8f_.5,16a5,g5,p,8p,8g5,8a5,8b5,c,8c.,16e,8d,8c,8b.5,16a5,g5,8f5,8e5,c5,8e.5,16c,f5,8f.5,16a5,g5,8a.5,16b5,c";
const char PROGMEM rtttl_library4[]="BarbieGirl:d=4,o=5,b=125:32e,32f#,8g#,8e,8g#,8c#6,a,8p,16p,16g#,8f#,8d#,8f#,8b,g#,8f#,8e,p,8e,8c#,f#,c#,p,8f#,8e,g#,f#,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,b,g#,e,c#4,16e,16p,16e,16p,8c#4,8b4,16e,16p,16e,16p,8c#4,8b4,8p,8c#6,8b,8c#6,8p,8c#6,8b,8c#6";
const char PROGMEM rtttl_library5[]="Doom:d=32,o=5,b=56:f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,f,f,f6,f,f,d#6,f,f,c#6,f,f,b,f,f,c6,c#6,f,f,f6,f,f,d#6,f,f,c#6,f,f,8b.,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,e6,a#,a#,f6,f#6,a#,a#,a#6,a#,a#,g#6,a#,a#,f#6,a#,a#,8e6";
const char PROGMEM rtttl_library6[]="ImBlue:d=4,o=6,b=63:16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#,16b,16d#7,16e7,16g#,16d#7,16c#7,16b,16d#,16g#,16b,16a#,16c#,16f#,8g#,16b5,16f#,8g#,16f#,16g#,16a#,16b,16d#,16g#,16b,16c#7,16f#,16a#,8b,16g#";
const char PROGMEM rtttl_library7[]="Tetris:d=4,o=6,b=80:8f7,16c7,16c#7,16d#7,32f7,32d#7,16c#7,16c7,8a#,16a#,16c#7,8f7,16d#7,16c#7,8c.7,16c#7,8d#7,8f7,8c#7,8a#,a#,8d#7,16f#7,8a#7,16g#7,16f#7,8f.7,16c#7,8f7,16d#7,16c#7,8c7,16c7,16c#7,8d#7,8f7,8c#7,8a#,8a#";
const char PROGMEM rtttl_library8[]="AmongUs:d=4,o=5,b=100:8c6,8d#6,8f6,8f#6,8f6,8d#6,8c6,4p,16a#5,16d6,16c6,16p,4p,8a#4,8c5,8p,8c6,8d#6,8f6,8f#6,8f6,8d#6,8f#6,4p,8p,12f#6,12f6,12d#6,12f#6,12f6,12d#6,8c5,8p";
	
// La siguiente matriz almacena las frecuencias de las notas musicales
const unsigned int note[4][12] =
{   // C    C#    D     D#    E     F     F#    G     G#    A     A#    B
	{262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494}, // 4ta octava
	{523,  554,  587,  622,  659,  698,  740,  784,  830,  880,  932,  988}, // 5ta octava
	{1047, 1109, 1175, 1244, 1319, 1397, 1480, 1568, 1660, 1760, 1865, 1976}, // 6ta octava
	{2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3320, 3520, 3728, 3951}  // 7ma octava
};

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


// Saco el sonido por el PIN9 del PORTD: freq en Hz, dur en ms
void sound(unsigned int freq, unsigned int dur)
{
	while (sound_playing);      // Si hay alg?n sonido presente, espero a que termine
	
	duration_timer = dur;       // Seteo el tiempo de duraci?n
	
	// Activo la salida y configuro el timer para que genere la se?al de la frecuencia apropiada
	TCCR1A|=(1<<COM1A0);
	
	// Actualizo el valor de OCR1A para que produzca la nota adecuada
	OCR1A=(8000000/(freq))-1;
	
	sound_playing = 1;          // Activo el flag para avisar que hay una nota sonando
}

// Esta funci?n reproduce una canci?n que se le pase en un string con formato RTTTL
void play_song()
{
	unsigned char temp_duration, temp_octave, current_note, dot_flag;
	unsigned int calc_duration;
	// read the musical notes
	if(menuFlag == REPRODUCIENDO && !sound_playing){
		current_note = 255;         // Nota por defecto = pausa
		temp_octave = octave;       // Seteo la octava a la por defecto de la canci?n
		temp_duration = duration;   // Seteo la duraci?n a la por defecto de la canci?n
		dot_flag = 0;               // Borro el flag de detecci?n de punto
		// Busco un prefijo de duraci?n
		if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
		{
			temp_duration = cancionRAM[lectorCancion] - '0';
			lectorCancion++;
			if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
			{
				temp_duration = temp_duration*10 + (cancionRAM[lectorCancion] - '0');
				lectorCancion++;
			}
		}
		// Busco una nota
		switch (cancionRAM[lectorCancion])
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
		lectorCancion++;                     // Avanzo al pr?ximo caracter
		// Busco un '#' siguiendo la nota
		if (cancionRAM[lectorCancion]=='#')
		{
			current_note++;   // Incremento la nota (A->A#, C->C#, D->D#, F->F#, G->G#)
			lectorCancion++;                   // Avanzo al pr?ximo caracter
		}




		// Busco '.' (extiende la duraci?n de la nota un 50%)
		if (cancionRAM[lectorCancion]=='.')
		{
			dot_flag = 1;             // Si se encuentra '.', seteo el flag
			lectorCancion++;                   // Avanzo al pr?ximo caracter
		}
		// Busco un sufijo de una octava
		if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
		{
			temp_octave = cancionRAM[lectorCancion] - '0';// Seteo la octava en consecuencia
			lectorCancion++;                   // Avanzo al pr?ximo caracter
		}
		if (cancionRAM[lectorCancion]=='.') // Un punto puede ser encontrado incluso despu?s de una octava
		{
			dot_flag = 1;             // Si se encuentra '.', seteo el flag
			lectorCancion++;                   // Avanzo al pr?ximo caracter
		}
		while (cancionRAM[lectorCancion] == ',') lectorCancion++;    // Salteo ','
		// Calculo la duraci?n de la nota
		calc_duration = (60000/tempo)/(temp_duration);
		calc_duration *= 4;         // La nota completa tiene cuatro beats
		// Chequeo si el flag de punto est? activado, de ser as?, extiendo la duraci?n en un 50%
		if (dot_flag) calc_duration = (calc_duration*3)/2;
		// Si la nota actual NO es una pausa, reproduzco la nota usando la funci?n sound
		if (current_note<255) sound(note[temp_octave-4][current_note],calc_duration);
		else
		{ // Si la nota actual es una pausa (255), espero dicha cantidad de tiempo
			duration_timer = calc_duration;
			sound_playing = 1;
		}
		if(!cancionRAM[lectorCancion]){
			menuFlag=STOP;
		}
	}else{
		if(menuFlag == CARGANDO){
			while (cancionRAM[lectorCancion] != ':') {
				lectorCancion++;  // Busca el primer ':'
				}
			lectorCancion++;     // Saltea el primer ':'
			while (cancionRAM[lectorCancion]!=':')            // Repite hasta encontrar ':'
			{
				if (cancionRAM[lectorCancion] == 'd')           // Entra si es el seteo de la duraci?n
				{
					duration = 0;             // Seteo la duraci?n en cero (temporalmente)
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					while (cancionRAM[lectorCancion] == '=') { 
						lectorCancion++;  // Salteo '='
						}
					while (cancionRAM[lectorCancion] == ' ') {lectorCancion++; } // Salteo los espacios
					// Si el caracter es un n?mero, seteo la duraci?n
					if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9') duration = cancionRAM[lectorCancion] - '0';
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					// Me fijo si el caracter es un n?mero, ya que la diraci?n puede ser de dos d?gitos de largo
					if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
					{ // Multiplico duraci?n por 10 y le agrego el valor del caracter
						duration = duration*10 + (cancionRAM[lectorCancion] - '0');
						lectorCancion++;                 // Avanzo al pr?ximo caracter
					}
					while (cancionRAM[lectorCancion] == ',') lectorCancion++;  // Salteo ','
				}
		
				if (cancionRAM[lectorCancion] == 'o')           // Entra si es el seteo de la octava
				{
					octave = 0;               // Seteo la octava en cero (temporalmente)
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					while (cancionRAM[lectorCancion] == '=') lectorCancion++;  // Salteo '='
					while (cancionRAM[lectorCancion] == ' ') lectorCancion++;  // Salteo los espacios
					// Si el caracter es un n?mero, seteo la octava
					if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9') octave = cancionRAM[lectorCancion] - '0';
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					while (cancionRAM[lectorCancion] == ',') lectorCancion++;  // Salteo ','
				}
				if (cancionRAM[lectorCancion] == 'b')           // Entra si es el seteo del tempo (beats por minuto)
				{
					tempo = 0;                // Seteo el tempo en cero (temporalmente)
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					while (cancionRAM[lectorCancion] == '=') lectorCancion++;  // Salteo '='
					while (cancionRAM[lectorCancion] == ' ') lectorCancion++;  // Salteo los espacios
					// Ahora leo el seteo del tempo (puede tener 3 d?gitos de largo)
					if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9') tempo = cancionRAM[lectorCancion] - '0';
					lectorCancion++;                   // Avanzo al pr?ximo caracter
					if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
					{
						tempo = tempo*10 + (cancionRAM[lectorCancion] - '0'); // El tempo tiene dos d?gitos
						lectorCancion++;                 // Avanzo al pr?ximo caracter
						if (cancionRAM[lectorCancion]>='0' && cancionRAM[lectorCancion]<='9')
						{
							tempo = tempo*10 + (cancionRAM[lectorCancion] - '0'); // El tempo tiene tres d?gitos
							lectorCancion++;               // Avanzo al pr?ximo caracter
						}
					}
					while (cancionRAM[lectorCancion] == ',') lectorCancion++;  // Salteo ','
				}
				while (cancionRAM[lectorCancion] == ',') lectorCancion++;    // Salteo ','
			}
			lectorCancion++;                       // Avanzo al pr?ximo caracter
			menuFlag = REPRODUCIR;
			
		}
	}
}

void reproducir(const char* flashAddress)
{
	int lenght = 2;
	int i = 0;
	char c;
	//Calculo el tamano de la cancion
	c = pgm_read_byte_near(flashAddress + i);
	while(c != '\0'){
		lenght++;
		i++;
		c = pgm_read_byte_near(flashAddress + i);
	}
	// Creo el array en RAM con el tamano necesario
	cancionRAM = (char*)malloc(lenght * sizeof(char));
	// Cargo la cancion en RAM
	for (i = 0; i < lenght - 1; i++) {
		c = pgm_read_byte_near(flashAddress + i);
		cancionRAM[i] = c;
	}
	cancionRAM[i] = '\0';
	lectorCancion=0;
	sound_playing=0;
	duration = 4;                 // Duraci?n est?ndar = 4/4 = 1 beat
	tempo = 63;                   // Tempo est?ndar = 63 bpm
	octave = 6;                   // Octava est?ndar = 6th
	play_song();
}

void printSongList(){
	//Envia lista de canciones desde ROM
	int i = 0; char c;
	c = pgm_read_byte_near(rtttlSongNames + i);
	while(c != '\0'){
		SerialPort_Wait_For_TX_Buffer_Free();
		SerialPort_Send_Data(c);
		i++;
		c = pgm_read_byte_near(rtttlSongNames + i);
	}
}

void eleccionMenu(char opcion){
	switch (opcion) {
		case '1':
			reproducir(rtttl_library1);
		break;
		case '2':
			reproducir(rtttl_library2);
		break;
		case '3':
			reproducir(rtttl_library3);
		break;
		case '4':
			reproducir(rtttl_library4);
		break;
		case '5':
			reproducir(rtttl_library5);
		break;
		case '6':
			reproducir(rtttl_library6);
		break;
		case '7':
			reproducir(rtttl_library7);
		break;
		case '8':
			reproducir(rtttl_library8);
		break;
		default:
			SerialPort_Send_String("Opcion invalida");
			menuFlag=STOP;
		break;
	}
}