#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define SPEED		150 	// possible range 0~255 PWM

int main(void)
{
	setup();
	float dist;
	setSpeed(SPEED, SPEED);

	while (1) {
		dist = getDist();
		printf("distance = %0.2f cm\n", dist);
		delay(10);
		
		/* Modify here */
		if ((dist < 10) && (dist > 5)) {
    			printf("go straight\n");
			setDir(FORWARD);
		}
		else if ((dist < 5) && (dist > 0)) {
    			printf("go straight\n");
			setDir(BACKWARD);
		}
		else {
			printf("stop\n");
			setDir(STOP);
		}
	}

	return 0;
}
