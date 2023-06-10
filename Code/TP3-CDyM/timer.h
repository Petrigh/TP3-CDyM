/*
 * timer.h
 *
 * Created: 5/6/2023 15:16:58
 *  Author: Infinio
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "avr/interrupt.h"
#include "ringtone.h"

unsigned int duration_timer;
volatile unsigned int sound_playing=0;

void TimerInit(void);



#endif /* TIMER_H_ */