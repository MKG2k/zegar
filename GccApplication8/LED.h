/*
 * LED.h
 *
 * Created: 09.06.2023 11:16:25
 *  Author: Michał
 */ 
#define LED1_PIN PINC1
#define LED1_DDR DDRC
#define LED1_PORT PORTC
#define LED1_SET LED1_PORT |= (1<<LED1_PIN)
#define LED1_CLR LED1_PORT &= ~(1<<LED1_PIN)

#define LED2_PIN PINC0
#define LED2_DDR DDRC
#define LED2_PORT PORTC
#define LED2_SET LED2_PORT |= (1<<LED2_PIN)
#define LED2_CLR LED2_PORT &= ~(1<<LED2_PIN)

void LEDSet(bool v, int ledNo);




