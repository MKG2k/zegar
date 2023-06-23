/*
 * Timer1.h
 *
 * Created: 23.06.2023 19:19:58
 *  Author: Michał
 */ 

#include "stdbool.h"
#ifndef TIMER1_H_
#define TIMER1_H_



void initTimer1();
volatile uint32_t Timer1Czas;

struct StopkaCzasu
{
uint32_t t1, t2;
bool CzyOdliczaCzas, WykonajAkcje;
};


#endif /* TIMER1_H_ */