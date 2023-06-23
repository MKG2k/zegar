/*
 * Przyciski.h
 *
 * Created: 09.06.2023 10:50:47
 *  Author: Michał
 */ 
#include "Timer1.h"

#define P1_PIN PB5
#define P1_STAN !(PINB & (1<<PINB5)) // true gdy wcisniety
#define P1_DDR DDRB
#define P1_PORT PORTB
void P1_init();
struct StopkaCzasu scP1;

#define P2_PIN PB4
#define P2_STAN !(PINB & (1<<PINB4))
#define P2_DDR DDRB
#define P2_PORT PORTB


#define P3_PIN PC2 //tylko do zmiany trybu
#define P3_STAN !(PINC & (1<<PINC2))
#define P3_DDR DDRC
#define P3_PORT PORTC


#define P4_PIN PC3 
#define P4_STAN !(PINC & (1<<PINC3))
#define P4_DDR DDRC
#define P4_PORT PORTC


void P2_init();
void P3_init();
void P4_init();


void ObsluzPrzyciskZmianyTrybu();