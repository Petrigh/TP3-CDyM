#ifndef MENU_H_
#define MENU_H_

typedef enum {STOP, CARGANDO, SILENCIO, REPRODUCIR, REPRODUCIENDO, SELECCIONANDO, RESET} mefMenu;
mefMenu menuFlag;
char mostrarBienvenida;
char mostrarMenu;
char theme;
uint8_t themeBool;

void printBienvenida(void);
void printMenu(void);
void opcionMenu(char);
void menuMef(void);



#endif /* MENU_H_ */