#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Speed */
#define SPEED	100 // possible range 0~255 PWM

int main(void)
{
	setup();
	
	// setSpeed(SPEED, SPEED);
	
	while (1) {
		//printf("go straight\n");
		//setDir(FORWARD);

		//printf("go back\n");
		//setDir(BACKWARD);
		//delay(150);
		
		printf("turn right\n");
		setDir(RIGHT);
		setSpeed(SPEED, SPEED);
		delay(300);
		
		//printf("turn left\n");
		//setDir(LEFT);
		//delay(250);
		
		/* Stop */
		setDir(STOP);
		delay(3000);
	}

	return 0;
}
