/*
 * Kropka.c
 *
 * Created: 09.06.2023 20:21:03
 *  Author: Michał
 */ 
#include <avr/io.h>
#include "Kropka.h"

volatile uint8_t kropka;

void obsluzKropke()
{
	if(kropka > 0)
	{
		K1_PORT |= (1<<K1_PIN);
	}
	else
	{
		K1_PORT &= ~(1<<K1_PIN);
	}
	
}