#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Speed */
#define SPEEDA	150 // possible range 0~255 PWM
#define SPEEDB	155

int main(void)
{
	setup();
		
	while (1) {
		move(FW, SPEEDA, SPEEDB);
	}

	return 0;
}
