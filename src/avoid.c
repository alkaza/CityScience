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
	int turning = 0;
	int straight = 0;
	int speed = SPEED;

	setSpeed(SPEED, SPEED);
	while (1) {
		dist = getDist();
		printf("dist = %0.2f cm\n", dist);
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			if (turning && (speed > 100)) {
				speed--;
				setSpeed(speed, speed);
			}
			else {
				straight = 0;
				turning = 1;
				speed = SPEED;
				setSpeed(0, 0);
				delay(300);
				printf("turn right\n");
				setDir(RIGHT);
				setSpeed(speed, speed);
			}
		}
		else {
			if (straight && (speed > 100)) {
				speed--;
				setSpeed(speed, speed);
			}
			else {	
				turning = 0;
				straight = 1;
				speed = SPEED;
				setSpeed(0, 0);
				delay(300);
				printf("go straight\n");
				setDir(FORWARD);
				setSpeed(speed, speed);
			}
		}
	}

	return 0;
}
