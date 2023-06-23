/*
 * Kropka.c
 *
 * Created: 09.06.2023 20:21:03
 *  Author: Michał
 */ 
#include <avr/io.h>
#include "Kropka.h"
#include <stdbool.h>


void obsluzKropke(bool kropka)
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
