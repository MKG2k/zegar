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
		K_PORT |= (1<<K_PIN);
	}
	else
	{
		K_PORT &= ~(1<<K_PIN);
	}
	
}
void ledSec(void)
{
	if(!(K_PIN & (1<<K_PIN)))
	{
		K_PORT |= (1<<K_PIN);
	}
	else
	{
		K_PORT &= ~(1<<K_PIN);
	}
}
void ustawLedSec()
{
	K_PORT |= (1<<K_PIN);
}
void zgasLedSec()
{
	K_PORT &= ~(1<<K_PIN);
}