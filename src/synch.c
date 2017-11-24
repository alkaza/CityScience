#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Speed */
#define SPEEDA	150 // possible range 0~255 PWM
#define SPEEDB	160
int main(void)
{
	setup();
	
	setSpeed(SPEEDA, SPEEDB);
	
	while (1) {
		setDir(FW);
	}

	return 0;
}
