/*
 * seos.h
 *
 * Created: 9/6/2023 21:11:32
 *  Author: Infinio
 */ 


#ifndef SEOS_H_
#define SEOS_H_

#include <avr/io.h>
#include "menu.h"

void SEOS_Schedule_Tasks (void); // Da la señal para que se actualizen los flags de UART y Menu
void SEOS_Dispatch_Tasks (void); // Actualiza UART y MENU si los flags se activan

#endif /* SEOS_H_ */