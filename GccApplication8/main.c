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
#include "Minutnik.h"
#include "Stoper.h"
#include "LicznikCzasu.h"
#include "Przyciski.h"
#include "LED.h"
#include "stdbool.h"
#include "Kropka.h"
#include "Timer1.h"

uint8_t tryb;
uint8_t flagaZatrzymania=0;
extern struct WyswietlaczStruktura Wyswietlacz; 



void ledSec(void);
void ustawLedSec();
void zgasLedSec();


	

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
	
	initTimer1();
	
	
	
	
	sei();
	Wyswietlacz.z1=1;
	Wyswietlacz.z2=2;
	Wyswietlacz.z3=3;
	Wyswietlacz.z4=4;

P1_init();
P2_init();
P3_init();
P4_init();
	
	
	
	DDRC|=(1<<PINC0);
	
	DDRD|=(1<<PIND0);


	uint8_t flagaPrzycisku=0;
	

	
	
	uint8_t hour, min, sec;
	
	rtc_get_time_s(&hour, &min, &sec);
	
	
	
	while(1) {
		
		LEDSet(false, LED2_PIN);
		
		
		
		switch (tryb)
		{
			case 0:
			
			
			rtc_get_time_s(&hour, &min, &sec);
			if(sec % 2 )
			{
				Wyswietlacz.k2 = 1;
				
				
			}
			else
			{
				Wyswietlacz.k2 = 0;
			}
			//min
			Wyswietlacz.z1 = hour/10;
			
			Wyswietlacz.z2 = (hour-(Wyswietlacz.z1*10));

			Wyswietlacz.z3 = min/10;
			
			Wyswietlacz.z4 = (min-(Wyswietlacz.z3*10));
			
			
			break;
			case 1: //tryb 2
			
			ObsluzPrzycisk(&flagaPrzycisku, &flagaZatrzymania);
			wyzerowanie();
			licznikStopera = licznikCzasu/10;
			if(licznikStopera > 100)
			{
				Wyswietlacz.k2 = 1;
			}
			else
			{
				Wyswietlacz.k2 = 0;
			}

			Wyswietlacz.z1 = licznikStopera/1000;

			Wyswietlacz.z2 = (licznikStopera-(Wyswietlacz.z1*1000))/100;
			
			Wyswietlacz.z3 = (licznikStopera-(Wyswietlacz.z1*1000)-(Wyswietlacz.z2*100))/10;

			Wyswietlacz.z4 = (licznikStopera-(Wyswietlacz.z1*1000)-(Wyswietlacz.z2*100)-(Wyswietlacz.z3*10));


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
				
			Wyswietlacz.z1 = licznikMinutnika/1000;

			Wyswietlacz.z2 = (licznikMinutnika-(Wyswietlacz.z1*1000))/100;
			
			Wyswietlacz.z3 = (licznikMinutnika-(Wyswietlacz.z1*1000)-(Wyswietlacz.z2*100))/10;

			Wyswietlacz.z4 = (licznikMinutnika-(Wyswietlacz.z1*1000)-(Wyswietlacz.z2*100)-(Wyswietlacz.z3*10));
			
			break;
			default:
			/* Your code here */
			break;
		}

		ObsluzPrzyciskZmianyTrybu();
	}
	

}

