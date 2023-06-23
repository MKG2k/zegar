/*
* Przyciski.c
*
* Created: 09.06.2023 10:50:32
*  Author: Michał
*/
#include <avr/io.h>
#include "Przyciski.h"
#include "stdbool.h"
#include "main.h"
#include "LED.h"
#include "Stoper.h"
void P1_init()
{
	P1_DDR&=~(1<<P1_PIN);
	P1_PORT|=(1<<P1_PIN);
}



void P2_init()
{
	P2_DDR&=~(1<<P2_PIN);
	P2_PORT|=(1<<P2_PIN);
}




void P3_init()
{
	P3_DDR&=~(1<<P3_PIN);
	P3_PORT|=(1<<P3_PIN);
}





void P4_init()
{
	P4_DDR&=~(1<<P4_PIN);
	P4_PORT|=(1<<P4_PIN);
}


void ObsluzPrzyciskZmianyTrybu()
{
	
	if(P3_STAN)
	{
		LEDSet(true, LED2_PIN);
		zmianaTrybuLed();
		tryb++;
		
		flagaZatrzymania = 1;
		licznikStopera = 0;
		
		
		if(tryb == 3)
		tryb = 0;
		LEDSet(false, LED2_PIN);
	}

}