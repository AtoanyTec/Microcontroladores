#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "pic18f4550_config.h" // Include configuration file 
#define F_CPU 8000000/64 // value to calculate baud rate
void MSdelay(unsigned int val)
{
unsigned int i,j;
for(i=0;i<=val;i++)
for(j=0;j<81;j++); 
}
void UART_Initial(long baud_rate)
{
float bps; 
TRISCbits.RC6=1;
TRISCbits.RC7=1;
bps = (( (float) (F_CPU) / (float) baud_rate) - 1); // sets baud rate
SPBRG=(int)bps; // store value for 9600 baud rate
TXSTAbits.CSRC = 0; // Don't care for asynchronous mode
TXSTAbits.TX9 = 0; // Selects 8-bit data transmission
TXSTAbits.TXEN = 1; // Enable Data tranmission on RC6 pin
TXSTAbits.SYNC = 0; // Selects Asynchronous Serial Communication Mode
TXSTAbits.BRGH = 0; // Default Baud rate speed 
BAUDCONbits.BRG16 = 0; // selects only 8 bit register for baud rate 
RCSTA = 0x90; // Enables UART Communication PORT

}

char USART_Read()
{
while(RCIF==0); // see if data on RC7 pin is available 
if(RCSTAbits.OERR)
{ 
CREN = 0;
NOP();
CREN=1;
}
return(RCREG); //read the byte from recieve register and return value
}
void main(void) 
{
char data;
OSCCON=0x72; // Select internal oscillator with frequency = 8MHz
TRISDbits.RD0=0; //Make RD0 pin as a output pin
PORTDbits.RD0=0; //initialize RD0 pin to logic zeeo
UART_Initial(9600);
while(1)
{
data=USART_Read();
if(data=='A')
PORTDbits.RD0=1;
else
PORTDbits.RD0=0;

}
return;
}