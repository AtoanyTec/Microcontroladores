/*
 * File:   main_repe
 * Author: Atoany Fierro
 * Tecnológico de Monterrey
 * Created on June 13, 2022, 4:08 PM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "fuses.h"


#define _XTAL_FREQ 20000000

void interrupcionGeneral(void);

unsigned char i = 0;
int unidades = 0;
int decenas = 0;
int UNI[10]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
int DEC[10]= {0b01111111,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};


void main(void) {
    
    ADCON1 = 0b11111111;
    
    TRISD = 0;
    TRISB = 0b00000001;
    
    //Registros de interrupciones
    TRISBbits.TRISB0 = 1; //  Configura el pin RB0 como entrada.
    INTCONbits.INT0IE = 1; //  Habilita interrupcion Externa INT0.
    INTCON2bits.INTEDG0 = 0; //  Interrupcion por flanco de bajada.
    INTCONbits.INT0IF = 0; //  Borra el flag de INT0IF.
    RCONbits.IPEN = 0; //  Deshabilita las Interrupciones de Prioridad.
    INTCONbits.PEIE = 1; //  Habilita interrupciones PERIFERICAS.
    INTCONbits.GIE = 1; //  Habilita Interrupcion GLOBAL.
    
    
    //Tarea X del PIC
    while (1) {
        LATB = DEC[decenas];
        LATD = UNI[unidades];
    }
}


//Tarea Y del PIC
void interrupt INT_EXT_0(void) 
{
    if (INTCONbits.INT0IF) 
    {
        unidades = unidades + 1;
        if(unidades == 10)
            {
                decenas = decenas + 1;
                unidades = 0;
            }
        INTCONbits.INT0IF = 0;
    }
}
