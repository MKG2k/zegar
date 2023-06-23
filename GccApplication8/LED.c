/*
* LED.c
*
* Created: 09.06.2023 11:16:38
*  Author: Michał
*/
#include <avr/io.h>
#include "stdbool.h"
#include "LED.h"
#include <util/delay.h>

void LEDSet(bool v, int ledNo)
{
	
	switch (ledNo)
	{		
		case LED1_PIN:
			if(v == true)
			{
				LED1_SET;
			}
			else
			{
				LED1_CLR;
			}
		break;
		case LED2_PIN:
			if(v == true)
			{
				LED2_SET;
			}
			else
			{
				LED2_CLR;
			}
		break;
		default:
		/* Your code here */
		break;
	}
	

}

void LED_init()
{
	LED1_DDR  |= (1<<LED1_PIN);
	LED1_PORT   &=~  (1<<LED1_PIN);
	
	LED2_DDR  |= (1<<LED2_PIN);
	LED2_PORT   &=~  (1<<LED2_PIN);
	
	
	
}


void zmianaTrybuLed()
{
	PORTC |= (1<<PINC1);
	_delay_ms(100);
	PORTC &= ~(1<<PINC1);
	_delay_ms(100);
}