#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Speed */
#define SPEED	150 // possible range 0~255 PWM

int main(void)
{
	setup();
	
	setSpeed(SPEED, SPEED);
	
	while (1) {
		//printf("go straight\n");
		//setDir(FORWARD);
		//delay(400);

		//printf("go back\n");
		//setDir(BACKWARD);
		//delay(200);
		
		printf("turn right\n");
		setDir(RIGHT);
		delay(300);
		
		//printf("turn left\n");
		//setDir(LEFT);
		//delay(300);
		
		/* Stop */
		brake()
		delay(3000);
	}

	return 0;
}
