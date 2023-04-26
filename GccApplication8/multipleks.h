/*
 * multipleks.h
 *
 *  Created on: 5 sty 2023
 *      Author: Michał
 */

#ifndef MULTIPLEKS_MULTIPLEKS_H_
#define MULTIPLEKS_MULTIPLEKS_H_


#define SEGMENTY_PORT		PORTD
#define SEGMENTY_DDR	DDRD

#define KATODY_PORT			PORTB
#define KATODY_DDR		DDRB

#define KATODA_1 			0b00000001
#define KATODA_2 			0b00000010
#define KATODA_3 			0b00000100
#define KATODA_4 			0b00001000
#define MASKA_KATODY 		(KATODA_1 | KATODA_2 | KATODA_3 | KATODA_4)

#define SEG_A				0b10000000
#define SEG_B				0b01000000
#define SEG_C				0b00100000
#define SEG_D				0b00010000
#define SEG_E				0b00001000
#define SEG_F				0b00000100
#define SEG_G				0b00000010

#define dataValue			0


extern uint8_t z1, z2, z3, z4;
extern volatile uint8_t kropka;

extern volatile uint8_t numerZnaku;

void multipleks_init( void );
void wyswietl(uint8_t segment, uint8_t cyfra);
unsigned int PodajZnak(uint8_t znak);

#endif /* MULTIPLEKS_MULTIPLEKS_H_ */
