/*
 * seos.c
 *
 * Created: 9/6/2023 21:11:21
 *  Author: Infinio
 */ 

#include "seos.h"

static uint8_t UART_flag = 1;
static uint8_t MENU_flag = 1;

void SEOS_Schedule_Tasks () {
	UART_flag = 1; // Actualizar periférico
	MENU_flag = 1; // Actualizar menu
}

void SEOS_Dispatch_Tasks () {
	if (MENU_flag){
		MENU_Update();
		MENU_flag = 0;
	}
	if (UART_flag){
		UART_Update();
		UART_flag = 0;
}
}
