
#ifndef RINGTONES_H_
#define RINGTONES_H_

#define CANCIONES 8

char* cancionRAM;
unsigned int lectorCancion;
unsigned int duration_timer;
volatile unsigned int sound_playing;
unsigned char duration, octave;
unsigned int tempo;
void reproducir(const char*);
void printSongList(void);
void eleccionMenu(char);
void play_song(void);


#endif /* RINGTONES_H_ */