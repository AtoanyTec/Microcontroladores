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

void escribir_eeprom(char direccion, char dato){
    while(EECON1bits.WR==1);  //1. esperar a que no haya una escritura en curso
                              
    EEADR=direccion;          //2. cargar la direccion
    EEDATA=dato;              //3. cargar el dato
    EECON1bits.EEPGD=0;       //4. setear EEPGD a 0
    EECON1bits.WREN=1;        //5. se habilita la escritura en la EEPROM 
    INTCONbits.GIE=0;         //6. deshabilitar las interrupcione
    EECON2=0x55;              //7. cargar en EECON2 0x55
    EECON2=0xaa;              //8. cargar en EECON2 0xaa
    EECON1bits.WR=1;          //9. iniciar la escritura en la EEPROM
    INTCONbits.GIE=1;         //10. habilitar las interrupciones
    EECON1bits.WREN=0;        //11. deshabilitar la escritura en la EEPROM
    while(EECON1bits.WR==1);  //12. comprobar que la escritura terminó
}
char leer_eeprom(char direccion){
    EEADR=direccion;      //1. cargar la direccion
    EECON1bits.EEPGD=0;   //2. acceso a la EEPROM
    EECON1bits.RD=1;      //3. habilitar la lectura de la EEPROM
    return EEDATA;        //4. en el registro EEDATA se encuentra el dato
                          
}
 
int main() {
//Configurando LCD
OpenXLCD(FOUR_BIT & LINES_5X7);
//Esperar hasta que el display esté disponible.
while(BusyXLCD());
//Mover cursor a la derecha...
WriteCmdXLCD(0x06);
//Desactivando el cursor.
WriteCmdXLCD(0x0C);

escribir_eeprom(0, 'W');
char letra;
//letra = leer_eeprom(0);
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
