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
uint8_t flagaZatrzymania=0;
uint16_t licznikStopera = 0;
uint16_t licznikMinutnika = 0;
uint16_t licznikMinutnikaStartowy = 0;
uint8_t flagaMinutnika = 0;
volatile uint32_t licznikCzasu = 0;
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
void wylaczLicznikCzasu()
{
	

	TCCR1B&=~(1<<CS11);
	TCCR1B&=~(1<<CS10);
	
	
}
void ObsluzPrzycisk(uint8_t *flagaPrzycisku, uint8_t *flagaZatrzymania)
{
	if(!(PINC & (1<<PINC3)))
	{
		if(*flagaPrzycisku==0)
		{
			*flagaPrzycisku=1;
			*flagaZatrzymania=1;
			wylaczLicznikCzasu();
			_delay_ms(100);
			while(!(PINC & (1<<PINC3))){}
			return;
		}
		
		else if( (*flagaPrzycisku==1)&&(*flagaZatrzymania==1))
		{
			
			*flagaPrzycisku=0;
			*flagaZatrzymania=0;
			_delay_ms(100);
			while(!(PINC & (1<<PINC3))){}
			return;
		}
		
	}
}

void MinutnikPrzyciskRozpoczynajacyOdliczanie()
{
	if(!(PINC & (1<<PINC3)))
	{
		while(!(PINC & (1<<PINC3))){}
		flagaMinutnika=1;
		
		
	}
}


void ObsluzPrzyciskZmianyTrybu()
{
	
	if(!(PINC & (1<<PINC2)))
	{
		ustawLed(true);
		zmianaTrybuLed();
		tryb++;
		
		flagaZatrzymania = 1;
		licznikStopera = 0;
		
		
		if(tryb == 3)
		tryb = 0;
		ustawLed(false);
	}

}

void uruchomLicznikCzasu()
{
	licznikCzasu = 0;
	TCCR1B |= (1<<CS11)|(1<<CS10);
}
void wyzerowanie()
{
	if(!(PINB & (1<<PINB4)))
	{
		while(!(PINB & (1<<PINB4))){}
		flagaZatrzymania=1;
		licznikStopera = 0;
		uruchomLicznikCzasu();
		
	}
}
void MinutnikWyzerowanie()
{
	if(!(PINB & (1<<PINB4)))
	{
		while(!(PINB & (1<<PINB4))){}
		licznikMinutnikaStartowy=licznikMinutnika;
		uruchomLicznikCzasu();
		
	}
}
void MinutnikZmianaWartosciWGore()
{
	if(!(PINB & (1<<PINB4)))
	{
		_delay_ms(100);
		
		if(!(PINB & (1<<PINB4))) licznikMinutnika++;

		
	}
}


void read_rtc(void)
{
	
	uint8_t hour, min, sec;
	rtc_get_time_s(&hour, &min, &sec);
}

ISR(	TIMER1_COMPA_vect	) {
	
	licznikCzasu ++;
	
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
	OCR1A = 12499;

	TIMSK |= (1<<OCIE1A);
	TCCR1B |= (1<<WGM12);
	
	
	
	
	sei();
	z1=1;
	z2=2;
	z3=3;
	z4=4;

	DDRC&=~(1<<PINC3);
	PORTC|=(1<<PINC3);
	
	DDRC&=~(1<<PINC2);
	PORTC|=(1<<PINC2);
	
	DDRB&=~(1<<PINB4);
	PORTB|=(1<<PINB4);
	
	DDRB&=~(1<<PINB5);
	PORTB|=(1<<PINB5);
	
	//DDRC&=~(1<<PINC1);
	//PORTC|=(1<<PINC1);
	
	DDRC|=(1<<PINC0);
	
	DDRD|=(1<<PIND0);


	uint8_t flagaPrzycisku=0;
	

	
	
	uint8_t hour, min, sec;
	
	rtc_get_time_s(&hour, &min, &sec);
	
	
	
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
			wyzerowanie();
			licznikStopera = licznikCzasu/10;
			if(licznikStopera > 100)
			{
				kropka = 1;
			}
			else
			{
				kropka = 0;
			}

			z1 = licznikStopera/1000;

			z2 = (licznikStopera-(z1*1000))/100;
			
			z3 = (licznikStopera-(z1*1000)-(z2*100))/10;

			z4 = (licznikStopera-(z1*1000)-(z2*100)-(z3*10));


			if(licznikStopera == 9999) wylaczLicznikCzasu();
			
			break;
			case 2:
				switch (flagaMinutnika)
				{
					case 0:
					
					MinutnikZmianaWartosciWGore();
					MinutnikPrzyciskRozpoczynajacyOdliczanie();
					
					break;
					
					case 1:
				
					MinutnikWyzerowanie();

					licznikMinutnika=licznikMinutnikaStartowy-(licznikCzasu/10);
				

					if(licznikMinutnika == 0) wylaczLicznikCzasu();
					break;
				}
				
			z1 = licznikMinutnika/1000;

			z2 = (licznikMinutnika-(z1*1000))/100;
			
			z3 = (licznikMinutnika-(z1*1000)-(z2*100))/10;

			z4 = (licznikMinutnika-(z1*1000)-(z2*100)-(z3*10));
			
			break;
			default:
			/* Your code here */
			break;
		}

		ObsluzPrzyciskZmianyTrybu();
	}
	

}

