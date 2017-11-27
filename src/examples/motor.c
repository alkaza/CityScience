#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Speed */
#define SPEEDA	150 // possible range 0~255 PWM
#define SPEEDB	150

int main(void)
{
	setup();
	
	setSpeed(SPEEDA, SPEEDB);
	
	while (1) {
		//printf("go straight\n");
		//setDir(FW);
		//delay(400);

		//printf("go back\n");
		//setDir(BW);
		//delay(200);
		
		printf("turn right\n");
		setDir(RIGHT);
		delay(300);
		
		//printf("turn left\n");
		//setDir(LEFT);
		//delay(300);
		
		/* Stop */
		brake();
		delay(3000);
	}

	return 0;
}
