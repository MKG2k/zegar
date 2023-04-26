/*
 * main_mp.c
 *
 *  Created on: 5 sty 2023
 *      Author: Michał
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "multipleks.h"



#define data_value = 0


//const uint8_t cyfry[] PROGMEM = {
		//(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F),			//0
		//(SEG_B|SEG_C),									//1
		//(SEG_A|SEG_B|SEG_G|SEG_E|SEG_D),				//2
		//(SEG_A|SEG_B|SEG_G|SEG_C|SEG_D),				//3
		//(SEG_F|SEG_G|SEG_B|SEG_C),						//4
		//(SEG_A|SEG_F|SEG_G|SEG_C|SEG_D),				//5
		//(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),			//6
		//(SEG_A|SEG_B|SEG_C),							//7
		//(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),	//8
		//(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),			//9
		//0x00											//10
//};

//uint8_t cyfra[4];
uint8_t z1, z2, z3, z4;
volatile uint8_t kropka;

volatile uint8_t numerZnaku=1;

volatile uint8_t katoda=0b00000001;

void obsluzKropke()
{
	if(kropka > 0)
	{
		PORTD |= (1<<PIND0);
	}
	else
	{
		PORTD &= ~(1<<PIND0);
	}
	
}

unsigned int PodajZnak(uint8_t znak)
{

	switch (znak)
	{
		case 0:
		return (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F);
		case 1:
		return (SEG_B|SEG_C) ;
		case 2:
		return (SEG_A|SEG_B|SEG_G|SEG_E|SEG_D);
		case 3:
		return (SEG_A|SEG_B|SEG_G|SEG_C|SEG_D);
		case 4:
		return (SEG_F|SEG_G|SEG_B|SEG_C);
		case 5:
		return(SEG_A|SEG_F|SEG_G|SEG_C|SEG_D);
		case 6:
		return (SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G);
		case 7:
		return (SEG_A|SEG_B|SEG_C);
		case 8:
		return (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G);
		case 9:
		return(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G);

		
		default:
		return (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F);
	}
	
}

void wyswietl(uint8_t segment, uint8_t cyfra)
{

	KATODY_PORT=0;

	switch (segment)
	{
		case 1:
		
		SEGMENTY_PORT =	PodajZnak(cyfra) ;//(SEG_A|SEG_B|SEG_G|SEG_C|SEG_D);
		KATODY_PORT=KATODA_1;
		
		
		break;
		case 2:
		SEGMENTY_PORT=	PodajZnak(cyfra) ;
		obsluzKropke();
		KATODY_PORT=KATODA_2;
		
		break;
		case 3:
		
		SEGMENTY_PORT=	PodajZnak(cyfra) ;
		KATODY_PORT=KATODA_3;
		
		break;
		case 4:
		SEGMENTY_PORT=	PodajZnak(cyfra) ;
		KATODY_PORT=KATODA_4;
		
		
		break;
		
		
		default:
		/* Your code here */
		break;
	}
}
void multipleks_init( void )	{
		SEGMENTY_DDR = 0xff;
		SEGMENTY_PORT = 0xff;

		KATODY_DDR |= KATODA_1 | KATODA_2 | KATODA_3 | KATODA_4;
		KATODY_PORT = 0x00;

		_delay_ms (1000);
		KATODY_PORT = 0xff;
		_delay_ms (1000);
		KATODY_PORT = 0x00;
		_delay_ms (1000);
		SEGMENTY_PORT = 0;

		TCCR2 |= (1<<WGM21);
		TCCR2 |= (1<<CS22)|(1<<CS21);
		OCR2 = 155;
		TIMSK |= (1<<OCIE2);
}

ISR(	TIMER2_COMP_vect	) {

	//static uint8_t licznik;

switch (numerZnaku)
{
	case 1:
	wyswietl(numerZnaku,z1);
	break;
		case 2:
		wyswietl(numerZnaku,z2);
		break;
			case 3:
			wyswietl(numerZnaku,z3);
			break;
				case 4:
				wyswietl(numerZnaku,z4);
				break;
	default:
	/* Your code here */
	break;
}
	

	numerZnaku++;
	if( numerZnaku > 4 ) numerZnaku = 1;
	
   


}

