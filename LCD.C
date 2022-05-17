/*
 * File:   eeprom.c
 * Author: Asus
 *
 * Created on 13 de abril de 2020, 05:41 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <plib/xlcd.h>
#include <plib/delays.h>
 
//BITS DE CONFIGURACION.....
#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF
#pragma config PWRT = OFF, BOR = OFF, VREGEN = OFF
#pragma config WDT = OFF, WDTPS = 32768
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF
 
#define _XTAL_FREQ 48000000
 
//Funciones requeridas por la librería XLCD
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);
 
int main() {
//Configurando LCD
OpenXLCD(FOUR_BIT & LINES_5X7);
//Esperar hasta que el display esté disponible.
while(BusyXLCD());
//Mover cursor a la derecha...
WriteCmdXLCD(0x06);
//Desactivando el cursor.
WriteCmdXLCD(0x0C);

char letra;
letra = 'A';
 
while(1)
{
    char simbolo = 8;
//Primera fila
SetDDRamAddr(0x00);
putrsXLCD("Letra: ");
//Segunda fila
SetDDRamAddr(0x40);
putcXLCD(letra);
}
}
 
void DelayFor18TCY(void)
{
Delay10TCYx(120);
}
 
void DelayPORXLCD(void)
{
Delay1KTCYx(180);
return;
}
 
void DelayXLCD(void)
{
Delay1KTCYx(60);
return;
}
