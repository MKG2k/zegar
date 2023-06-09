/*
 * LicznikCzasu.c
 *
 * Created: 09.06.2023 10:38:45
 *  Author: Michał
 */ 
#include <avr/io.h>

volatile uint32_t licznikCzasu = 0;

void wylaczLicznikCzasu()
{
	

	TCCR1B&=~(1<<CS11);
	TCCR1B&=~(1<<CS10);
	
	
}
void uruchomLicznikCzasu()
{
	licznikCzasu = 0;
	TCCR1B |= (1<<CS11)|(1<<CS10);
}