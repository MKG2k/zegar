/*
* LED.c
*
* Created: 09.06.2023 11:16:38
*  Author: Michał
*/
#include <avr/io.h>
#include "stdbool.h"
#include "LED.h"

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