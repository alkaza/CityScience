#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINRANGE	5	// possible range 2~400 cm (3.3V)
#define SPEED		200 	// possible range 0~255 PWM

int main(void)
{
	setup();
	float dist;
	setSpeed(SPEED, SPEED);
	
	while (1) {
		dist = getDist();
		printf("dist = %0.2f cm\n", dist);
		delay(10);
		
		/* Modify here */
		if ((dist < MINRANGE) && (dist > 0)) {
			printf("turn right\n");
			setDir(RIGHT);
		}
		else {
			printf("go straight\n");
			setDir(FORWARD);
		}
	}

	return 0;
}
