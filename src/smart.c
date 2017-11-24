#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define SPEEDA		150 	// possible range 60~255 PWM
#define SPEEDB		155

volatile int smartflag = 0;

int main(void)
{
	setup();
	float dist;
	
	while (1) {
		dist = calc_dist();
		delay(10);
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			if (smartflag==1) {
				move(LEFT, SPEEDA, SPEEDB);
				smartflag = 0;
			}
			else {
				move(RIGHT, SPEEDA, SPEEDB);
				smartflag = 1;
			}
		}
		else {
			move(FW, SPEEDA, SPEEDB);
		}
	}

	return 0;
}
