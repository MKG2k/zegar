/*
 * Kropka.h
 *
 * Created: 09.06.2023 20:21:16
 *  Author: Michał
 */ 




#define K_PIN PD0
#define K_STAN
#define K_DDR DDRD
#define K_PORT PORTD


void obsluzKropke();
void ledSec(void);
void ustawLedSec();
void zgasLedSec();