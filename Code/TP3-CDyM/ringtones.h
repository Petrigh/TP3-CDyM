/*
 * ringtones.h
 *
 * Created: 18/06/2023 17:48:23
 *  Author: lylab
 */ 


#ifndef RINGTONES_H_
#define RINGTONES_H_

#define CANCIONES 8

volatile unsigned int sound_playing;
void reproducir(const char*);
void printSongList(void);
void eleccionMenu(char);


#endif /* RINGTONES_H_ */