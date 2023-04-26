/*
 * GccApplication5.c
 *
 * Created: 13.01.2023 15:36:50
 * Author : Michał
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "rtc.h"
#include "twi.h"
#include "multipleks.h"

volatile unsigned int stoper = 1;
	uint8_t tryb;
	
void ustawLed(bool v)
{
	if(v == true)
	{
		PORTC |= (1<<PINC0);
	}
	else
	{
		PORTC &= ~(1<<PINC0);
	}
}
void ledSec(void)
{
	if(!(PIND & (1<<PIND0)))
	{
		PORTD |= (1<<PIND0);
	}
	else
	{
		PORTD &= ~(1<<PIND0);
	}
}
void ustawLedSec()
{
	PORTD |= (1<<PIND0);
}
void zgasLedSec()
{
	PORTD &= ~(1<<PIND0);
}
void zmianaTrybuLed()
{
	PORTC |= (1<<PINC1);
	_delay_ms(100);
	PORTC &= ~(1<<PINC1);
	_delay_ms(100);
}

void ObsluzPrzycisk(uint8_t *flagaPrzycisku, uint8_t *flagaZatrzymania)
{
	if(!(PINC & (1<<PINC3)))
	{
		if(*flagaPrzycisku==0)
		{
			*flagaPrzycisku=1;
			*flagaZatrzymania=1;
			_delay_ms(100);
			return;
		}
		
		else if( (*flagaPrzycisku==1)&&(*flagaZatrzymania==1))
		{
			
			*flagaPrzycisku=0;
			*flagaZatrzymania=0;
			_delay_ms(100);
			return;
		}
		
	}
}

void ObsluzPrzyciskZmianyTrybu()
{ 
	
	if(!(PINC & (1<<PINC2)))
	{
		ustawLed(true);
		zmianaTrybuLed();
		tryb++;
				
		while(!(PINC & (1<<PINC2))){}
		if(tryb == 3)
		tryb = 0;
		ustawLed(false);
}

}



void read_rtc(void)
{
	
		uint8_t hour, min, sec;
		rtc_get_time_s(&hour, &min, &sec);
}



int main(void){

	multipleks_init();
	twi_init_master();
	//rtc_init();
	//podawanie stanu wysokiego na segmenty
	//SEGMENTY_PORT = (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G);
	//podawanie stanu wysokiego na tranzystory (stan niski na katodę)
	//KATODY_PORT = (KATODA_1|KATODA_2|KATODA_3|KATODA_4);

//unsigned char sec, temp;
//sec = 0;
//struct rtc_time ds1302;
//struct rtc_time *rtc;
//rtc = &ds1302;

//ds1302_init();
//ds1302_update(rtc);   // update all fields in the struct
//ds1302_set_time(rtc, SEC, 31);	//set the seconds to 31

	//cyfra[0] = 1;
	//cyfra[1] = 1;
	//cyfra[2] = 1;
	//cyfra[3] = 1;
	uint16_t licznik = 0;
	sei();
	z1=1;
	z2=2;
	z3=3;
	z4=4;

	DDRC&=~(1<<PINC3);
	PORTC|=(1<<PINC3);
	
	DDRC&=~(1<<PINC2);
	PORTC|=(1<<PINC2);
	
	//DDRC&=~(1<<PINC1);
	//PORTC|=(1<<PINC1);
	
	DDRC|=(1<<PINC0);
	
	DDRD|=(1<<PIND0);


	uint8_t flagaPrzycisku=0;
	uint8_t flagaZatrzymania=0;

		uint8_t zz1, zz2, zz3, zz4;
				
			uint8_t hour, min, sec;
			
			rtc_get_time_s(&hour, &min, &sec);
			
			uint8_t oldSec = sec;
	
	while(1) {
		
		ustawLed(false);
		
		
			
			switch (tryb)
			{
				case 0:
						
						
							rtc_get_time_s(&hour, &min, &sec);
							if(sec % 2 )
							{
								kropka = 1;
								
								
							}
							else
							{
								kropka = 0;
							}
							//min
							z1 = hour/10;
			
							z2 = (hour-(z1*10));

							z3 = min/10;
							
							z4 = (min-(z3*10));
	
							
				break;
				case 1: //tryb 2
							
							ObsluzPrzycisk(&flagaPrzycisku, &flagaZatrzymania);


							if(licznik > 100)
							{
								kropka = 1;
							}
							else
							{
								kropka = 0;
							}

							z1 = licznik/1000;

							z2 = (licznik-(z1*1000))/100;
	
							z3 = (licznik-(z1*1000)-(z2*100))/10;

							z4 = (licznik-(z1*1000)-(z2*100)-(z3*10));

							_delay_ms(50);

							if(flagaZatrzymania==0)
							{
								licznik++;
							}

							if(licznik == 9999) licznik = 0;
				break;
				case 2:
							
							ObsluzPrzycisk(&flagaPrzycisku, &flagaZatrzymania);

							z1 = licznik/1000;

							z2 = (licznik-(z1*1000))/100;
							
							z3 = (licznik-(z1*1000)-(z2*100))/10;

							z4 = (licznik-(z1*1000)-(z2*100)-(z3*10));

							_delay_ms(50);

							if(flagaZatrzymania==0)
							{
								licznik--;
							}

							if(licznik == 9999) licznik = 0;
				
				break;
				default:
				/* Your code here */
				break;
			}

	ObsluzPrzyciskZmianyTrybu();
	}
	

}

