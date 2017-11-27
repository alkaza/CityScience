#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define SPEEDA		150 	// possible range 60~255 PWM
#define SPEEDB		150

int turning = 0;
char turn_dir;

int main(void)
{
	setup();
	float dist;
	while (1) {
		dist = calc_dist();
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			if(prev_dir == FW){
				if (turning) {
					turning = 0;
					turn_dir = LEFT;
				}
				else {
					turning = 1;
					turn_dir = RIGHT;
				}
			}
			move_slow(turn_dir, SPEEDA, SPEEDB);
		}
		else {
			move_slow(FW, SPEEDA, SPEEDB);
		}
	}

	return 0;
}
