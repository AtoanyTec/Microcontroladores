/*
 * File:   main_ADC.c
 * Author: Asus
 *
 * Created on 5 de marzo de 2020, 06:53 PM
 */

#include <xc.h>
#include <XLCD.h>
#include <plib/delays.h>
#include <stdio.h>
#include <stdlib.h>
#include <plib/adc.h>    

#define _XTAL_FREQ 20000000

void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);

int resultado, unidad, decena;

void main(void) {
    
    //Configurando LCD 4 bits mutilínea
    OpenXLCD(FOUR_BIT & LINES_5X7);
    //Esperar hasta que el display esté disponible.
    while(BusyXLCD());
    //Mover cursor a la derecha...
    WriteCmdXLCD(0x06);
    //Desactivando el cursor.
    WriteCmdXLCD(0x0C);
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    OpenADC(ADC_FOSC_64 &
    ADC_RIGHT_JUST &
    ADC_16_TAD,
    ADC_CH0 &
    ADC_INT_OFF &
    ADC_VREFPLUS_VDD &
    ADC_VREFMINUS_VSS,
    14);
 
     //Retardo de 50 Tcy
    Delay10TCYx(5);
 
         while(1){
            //Inicio de la conversión
            ConvertADC();
 
             //Espera a que termine la conversion
            while(BusyADC());
 
            //Obteniendo el resultado
            resultado = ReadADC();
 
             //El resultado es un numero de 10 bits. Ya que solo se cuenta con un puerto
            resultado = (resultado*5)/1023;
            
            unidad = resultado % 10;
            decena = (resultado - unidad)/10;
            
            //Primera línea
            SetDDRamAddr(0x00);
            putrsXLCD("TEMP");
            //Segunda línea
            SetDDRamAddr(0x40);
            putcXLCD(decena+48);
            SetDDRamAddr(0x41);
            putcXLCD(unidad+48);
        }
}
void DelayFor18TCY(void){
 Delay10TCYx(120);
}
void DelayPORXLCD(void){
 Delay1KTCYx(75);
 return;
}
void DelayXLCD(void){
 Delay1KTCYx(25);
 return;
}
