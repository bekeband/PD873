
#include <pic.h>
#include "beeps.h"
#include "buttons.h"
#include "delay.h"

void Beep1(void) {

	unsigned char t=150;

	while(--t) {
		BUZZ2 = OFF;
		BUZZ1 = ON;
		Delay(DELAY_125us);
		BUZZ1 = OFF;
		BUZZ2 = ON;
	 	Delay(DELAY_125us);
	}
}

void Beep2(void) {

	unsigned char t=75;

	while(--t) {
		BUZZ2 = OFF;
		BUZZ1 = ON;
		Delay(DELAY_250us);
		BUZZ1 = OFF;
		BUZZ2 = ON;
	 	Delay(DELAY_250us);
	}
}

