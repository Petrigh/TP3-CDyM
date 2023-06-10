/*
 * seos.c
 *
 * Created: 9/6/2023 21:11:21
 *  Author: Infinio
 */ 

#include "seos.h"
#include "menu.h"

static uint8_t UART_flag = 0;
static uint8_t MENU_flag = 0;

void SEOS_Schedule_Tasks () {
	UART_flag = 1; // Actualizar periférico
	MENU_flag = 1; // Actualizar menu
}

void SEOS_Dispatch_Tasks () {
	if (UART_flag){
		UART_flag = 0;
		UART_Update();
	}
	if (MENU_flag){
		MENU_flag = 0;
		MENU_Command_Update();
	}
}
