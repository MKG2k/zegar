/*
 * Minutnik.c
 *
 * Created: 09.06.2023 10:27:04
 *  Author: Michał
 */ 
#include <avr/io.h>
#include "LicznikCzasu.h"
#include <util/delay.h>

uint16_t licznikMinutnika = 0;
uint16_t licznikMinutnikaStartowy = 0;
uint8_t flagaMinutnika = 0;

void MinutnikPrzyciskRozpoczynajacyOdliczanie()
{
	if(!(PINC & (1<<PINC3)))
	{
		while(!(PINC & (1<<PINC3))){}
		flagaMinutnika=1;
		
		
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