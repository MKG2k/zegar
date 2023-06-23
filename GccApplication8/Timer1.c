/*
 * Timer1.c
 *
 * Created: 23.06.2023 19:19:43
 *  Author: Michał
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdbool.h"
#include "Timer1.h"

ISR(	TIMER1_COMPA_vect	) {
	
	Timer1Czas ++;
	
}

void initTimer1()
{
		OCR1A = 12499;

		TIMSK |= (1<<OCIE1A);
		TCCR1B |= (1<<WGM12);
		
		TCCR1B |= (1<<CS11)|(1<<CS10);
}

void ZweryfikujPrzycisk(struct StopkaCzasu *sc, bool *StanPinu)
{
	 if(*StanPinu == 0)
	 {
		 if(*sc->CzyOdliczaCzas == false)
		 {
			*sc->CzyOdliczaCzas = true;
			*sc->t1 = Timer1Czas;
		 }
	 }
	 else
	 {
		 if(*sc->CzyOdliczaCzas == true)
		 {
			*sc->CzyOdliczaCzas = false;
			*sc->t2 = Timer1Czas;
			*sc->WykonajAkcje; 
		 }
	 }
}