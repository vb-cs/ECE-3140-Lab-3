#include "3140_concur.h"
#include "utils.h"

// We will be stealing this blinking function again, with a slight modification
void p1 (void) {
	LEDGreen_Off();
	int i;
	for (i=0; i < 6; i++) {
		delay ();
    	LEDRed_Toggle();
	}
}

// p2 has an infinite loop! This should be no match for our round robin, though!
void p2 (void) {
	LEDRed_Off();
	while (1)
		LEDGreen_On();
}

void p3 (void) {
	int i;
		for (i=0; i < 10; i++) {
			delay ();
	    	LEDGreen_Toggle();
		}
}

int main (void) {
	LED_Initialize();

	if (process_create (p1,32) < 0) {
		return -1;
	}

	if (process_create (p2,32) < 0) {
			return -1;
		}

	if (process_create (p3,32) < 0) {
			return -1;
		}

	process_start ();

	/*
	This is our our original test! We once again are toggling the
	red LED a few times, except now, the green light should turn
	for a while intermittenly. Now, the infinite loop in p2 could
	possibly cause problems and just get the green LED stuck on
	forever, but our round robin scheduler should handle it with
	no problem! So, the green LED will also be toggled a few
	times, until both the red LED and green LED stop blinking and
	the green LED just stays on.
	 */

	while (1) ;

	return 0;
}
