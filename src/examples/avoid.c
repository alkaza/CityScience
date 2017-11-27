#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define SPEEDA		120 	// possible range 60~255 PWM
#define SPEEDB		130

int main(void)
{
	setup();
	float dist;
	while (1) {
		dist = calc_dist();
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			move_slow(RIGHT, SPEEDA, SPEEDB);
		}
		else {
			move_slow(FW, SPEEDA, SPEEDB);
		}
	}

	return 0;
}