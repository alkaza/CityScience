#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define SPEED		120 	// possible range 60~255 PWM

int main(void)
{
	setup();
	float dist;
	while (1) {
		dist = calc_dist();
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			move_slow(RIGHT, SPEED, SPEED);
		}
		else {
			move_slow(FW, SPEED, SPEED);
		}
	}

	return 0;
}
