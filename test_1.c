#include "3140_concur.h"
#include "utils.h"

// We will be stealing this blinking function, thank you very much!
void p1 (void) {
	int i;
	for (i=0; i < 6; i++) {
		delay ();
    	LEDRed_Toggle();
	}
}

int main (void) {
	LED_Initialize();

	if (process_create (p1,32) < 0) {
		return -1;
	}

	process_start ();

	/*
	This is our unoriginal test, the idea for which we stole from the
	document. We create a single process, returning -1 if creating the
	process produces an error of course. Then, we attempt to run the
	single process, ensuring this edge case works just fine. The
	process should, of course, simply toggle the red LED 6 times.
	 */

	while (1) ;

	return 0;
}
