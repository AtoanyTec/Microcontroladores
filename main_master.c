#include <xc.h> // Includes header file for PIC Microcontroller
//#include "pic18f4550_config.h" // Include configuration file 
#define F_CPU 8000000/64 // value to calculate baud rate
// This function used to generate delay in miliseconds
void MSdelay(unsigned int val)
{
unsigned int i,j;
for(i=0;i<=val;i++)
for(j=0;j<81;j++); 
}
//This function initialize UART module
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

void UART_Write( char data )
{
//while (TXIF == 0); 
TXREG = data; 
while(TRMT==0); // wait until transmit register not empty
}
void main(void) 
{
OSCCON=0x72; // Select internal oscillator with frequency = 8MHz
UART_Initial(9600);
while(1)
{

UART_Write('A'); // Send character A
MSdelay(1000); // adds delay of one second
}
return;
}