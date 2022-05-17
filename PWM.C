/*
 * File:   pwm.c
 * Author: Asus
 *
 * Created on 25 de marzo de 2020, 04:16 PM
 */


#include <xc.h>
#include <plib/timers.h>
#include <plib/pwm.h>
 
//BITS DE CONFIGURACION...

#pragma config PLLDIV = 5, CPUDIV = OSC1_PLL2, USBDIV = 2
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF
#pragma config PWRT = OFF, BOR = OFF, VREGEN = OFF
#pragma config WDT = OFF, WDTPS = 32768
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF
 
#define _XTAL_FREQ 20000000
 
void main(){
//TRISCbits.TRISC2 = 0;
TRISC = 0;

unsigned char prescaler = T2_PS_1_16;

OpenTimer2(prescaler);

OpenPWM1(0x68);

while(1)
{
SetDCPWM1(208);
}

}
