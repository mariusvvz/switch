/** C O N F I G U R AT I O N B I T S ******************************/
#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF 
#pragma config PWRTEN = OFF, BOREN = OFF
#pragma config WDTEN = OFF 
#pragma config MCLRE = EXTMCLR,  PBADEN = OFF
#pragma config STVREN = ON, LVP = OFF, XINST = OFF 
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF 
#pragma config CPB = OFF, CPD = OFF 
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF 
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF 
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF 
#pragma config EBTRB = OFF 

//#include <p18f45k22.h>
#include <delays.h>
//#include <stdio.h>
//#include <math.h>
//#include <USART.h>
//#include <stdlib.h>

#define START1 PORTAbits.RA0
#define DONE1 PORTAbits.RA1
#define START_LED1 PORTAbits.RA2
#define DONE_LED1 PORTAbits.RA3
#define START PORTAbits.RA4
#define DONE PORTAbits.RA5
#define START_LED PORTEbits.RE0
#define DONE_LED PORTEbits.RE1
#define F4 PORTBbits.RB1
#define F6 PORTBbits.RB2
#define ENTER PORTBbits.RB3
//-----------------------------------------------
//Prototipes:
void Delay10KTCYx(PARAM_SCLASS unsigned char);
void Delay1KTCYx(unsigned char unit);
void delay ( void);
void main(void);
void flash_start (void);
void flash_done (void);


void main(void)
{	
	int start_flag;
	int done_flag;
	
  	//Set the Fosc to 4MHz
  	OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 1;

 	//USART SETUP

	TRISCbits.TRISC6 = 1;	//For all modes of EUSART operation, the TRIS control
	TRISCbits.TRISC7 = 1;	//bits corresponding to the RXx/DTx and TXx/CKx pins
							//should be set to ‘1’.( DATASHEET P264)

	TXSTA1bits.SYNC=0;		//Asynchronous mode
    TXSTA1bits.TXEN=1;		//Transmit enabled
	RCSTA1bits.SPEN=1;		//Serial port enabled (configures RXx/DTx and TXx/CKx pins as serial port pins)

	TXSTA1bits.TX9=0;		//8-bit transmission
	TXSTA1bits.BRGH=1;		//high speed
	BAUDCON1bits.BRG16=0;	//8-BIT BAUD GENERATOR IS USED
    RCSTA1bits.CREN = 1; 	//Enable continuous reception

	SPBRG = 25;				// 9600 Baudrate

	//interrupt
    PIE1bits.RC1IE = 1;		//EUSART1 Receive Interrupt Enable bit
    INTCONbits.PEIE = 1;	//Enables all unmasked peripheral interrupts
    INTCONbits.GIE = 1;
    PIR1bits.RCIF = 0; 		//clear USART flag

	//PORT SETUP
	PORTA = 0;	//Clear port A
	LATA = 0;	
	TRISA = 0b00110011;	//TRIS=1 (INPUT) //TRIS =0 (OUTPUT)
	ANSELA = 0b11001100;

	PORTE = 0;	//Clear port E
	LATE = 0;
	TRISE = 0b00000000;

	PORTB = 0;	//Clear port A
	LATB = 0;	
	TRISB = 0b00000000;	//TRIS=1 (INPUT) //TRIS =0 (OUTPUT)

		
	START_LED1 = 0;	// turn of LED's
	DONE_LED1 = 0;
	START_LED = 0;	
	DONE_LED = 0;

	start_flag = 0;
    done_flag = 1;

	Delay10KTCYx(60);	//The full range of [0,255] is supported.

	START_LED = 1;		//turn on start led	
	done_flag = 1;
	Delay10KTCYx(250);
	start_flag = 0;

while (1)
{
	if (START && done_flag == 1)
		{	
			done_flag = 0;
			start_flag = 1;
			flash_start();		// flash start led
			F6 = 1;
			Delay10KTCYx(5);
			F6 = 0;
			F4 = 1;
			Delay10KTCYx(5);			
			F4 = 0;
			delay();
			Delay10KTCYx(250);
	//		Delay10KTCYx(200);
			DONE_LED = 1;
			Delay10KTCYx(10);
			DONE_LED = 0;
			Delay10KTCYx(10);
			DONE_LED = 1;
			Delay10KTCYx(10);
			DONE_LED = 0;
			Delay10KTCYx(10);
			DONE_LED = 1;
			
		}
		
		if (DONE && start_flag == 1)
			{
				start_flag = 0;
				done_flag = 1;
				flash_done();
				ENTER = 1;
				Delay10KTCYx(5);
				ENTER = 0;
				Delay10KTCYx(200);
				Delay10KTCYx(200);
				//Delay10KTCYx(200);
				Delay10KTCYx(100);
				F6 = 1;
				Delay10KTCYx(5);			
				F6 = 0;
				START_LED = 1;
			}
			
}
}


void flash_start (void)
{	
		START_LED = 1;
		Delay10KTCYx(20);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(20);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(10);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(5);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(2);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(2);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(1);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(1);	//1S DELAY
		START_LED = 1;
		Delay10KTCYx(2);	//1S DELAY
		START_LED = 0;
		Delay10KTCYx(2);	//1S DELAY
		START_LED = 0;
return;
}

void flash_done (void)
{	
		DONE_LED = 1;
		Delay10KTCYx(20);
		DONE_LED = 0;
		Delay10KTCYx(20);
		DONE_LED = 1;
		Delay10KTCYx(10);
		DONE_LED = 0;
		Delay10KTCYx(10);
		DONE_LED = 1;
		Delay10KTCYx(10);
		DONE_LED = 0;
		Delay10KTCYx(10);
		DONE_LED = 1;
		Delay10KTCYx(10);
		DONE_LED = 0;
		Delay10KTCYx(10);
		DONE_LED = 1;
		Delay10KTCYx(10);
		DONE_LED = 0;
		Delay10KTCYx(10);
		DONE_LED = 1;
		Delay10KTCYx(5);
		DONE_LED = 0;
		Delay10KTCYx(5);
		DONE_LED = 1;
		Delay10KTCYx(5);
		DONE_LED = 0;
		Delay10KTCYx(5);
		DONE_LED = 1;
		Delay10KTCYx(5);
		DONE_LED = 0;
		Delay10KTCYx(5);
return;
}

void delay ( void)
{
	int k = 0;
	for(k=0; k<10; k++)	//
		{
		Delay10KTCYx(200);	//2S DELAY
		}
	k = 0;
return;
}