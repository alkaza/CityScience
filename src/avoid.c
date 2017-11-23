#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define MAXSPEED	120 	// possible range 0~255 PWM
#define MINSPEED	60

int main(void)
{
	setup();
	float dist;
	while (1) {
		dist = calc_dist();
		/* Debugging */
		printf("dist = %0.2f cm\n", dist);
		printf("speed = %d\n", speed);
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			move(FW, MAXSPEED, MINSPEED);
		}
		else {
			move(RIGHT, MAXSPEED, MINSPEED);
		}
	}

	return 0;
}
