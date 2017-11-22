#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Macros */
#define MINDIST		10	// possible range 2~400 cm (3.3V)
#define MAXSPEED	150 	// possible range 0~255 PWM
#define MINSPEED	100
#define BRAKE		0

int turning = 0;
int straight = 0;
int speed = MAXSPEED;

int main(void)
{
	setup();
	float dist;
	while (1) {
		dist = getDist();
		printf("dist = %0.2f cm\n", dist);
		printf("speed = %d\n", speed);
		delay(10);
		
		/* Modify here */
		if ((dist < MINDIST) && (dist > 0)) {
			if (turning) {
				if (speed > MINSPEED){
					speed-=1;
				}
				setSpeed(speed, speed);
			}
			else {
				straight = 0;
				turning = 1;
				speed = MAXSPEED;
				
				setSpeed(BRAKE, BRAKE);
				delay(500);
				
				printf("turn right\n");
				setDir(RIGHT);
				setSpeed(speed, speed);
			}
		}
		else {
			if (straight) {
				if (speed > MINSPEED){
					speed-=1;
				}
				setSpeed(speed, speed);
			}
			else {	
				turning = 0;
				straight = 1;
				speed = MAXSPEED;
				
				printf("go straight\n");
				setDir(FORWARD);
				setSpeed(speed, speed);
			}
		}
	}

	return 0;
}
