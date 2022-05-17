
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "fuses2.h"


//#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
//#pragma config WDT = OFF // Watchdog Timer Enable bit (WDT enabled)
//#pragma config PWRT = OFF // Power-up Timer Enable bit (PWRT disabled)
//#pragma config BOR = ON // Brown-out Reset Enable bit (BOR enabled)
//#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//END CONFIG


#define _XTAL_FREQ 20000000

void interrupcionGeneral(void);

unsigned char i = 0;

void main(void) {
    
    ADCON1 = 0b11111111;
    
    TRISD = 0xF0; //  Configura el PUERTO D como salida.
    TRISB = 0x00;
    
    
    TRISBbits.TRISB0 = 1; //  Configura el pin RB0 como entrada.
    INTCONbits.INT0IE = 1; //  Habilita interrupcion Externa INT0.
    INTCON2bits.INTEDG0 = 0; //  Interrupcion por flanco de bajada.
    INTCONbits.INT0IF = 0; //  Borra el flag de INT0IF.
    RCONbits.IPEN = 0; //  Deshabilita las Interrupciones de Prioridad.
    INTCONbits.PEIE = 1; //  Habilita interrupciones PERIFERICAS.
    INTCONbits.GIE = 1; //  Habilita Interrupcion GLOBAL.
    
    while (1) {
        //LATDbits.LD4 = 1;
        //PORTBbits.RB0 = 1;
        PORTDbits.RD0 = 1;
        __delay_ms(30);
        //LATDbits.LD4 = 0;
        //PORTBbits.RB0 = 0;
        PORTDbits.RD0 = 0;
        __delay_ms(30);
    }
}


void interrupt INT_EXT_0(void) 
{
    if (INTCONbits.INT0IF) 
    {
        
        for(int i = 0; i<10; i++)
        {
            PORTDbits.RD1 = 1;
            __delay_ms(30);

            PORTDbits.RD1= 0;
            __delay_ms(30);
        }
        
        INTCONbits.INT0IF = 0;
    }
}

/*

void interrupt INT_EXT_0(void) 
{
    if (INTCONbits.INT0IF) 
    {
        INTCONbits.INT0IF = 0;
        if (++i == 16) 
        {
            i = 0;
        }
        LATD = i;
    }
}
*/
