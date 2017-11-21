#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

int main(void)
{
	setup();
	
	float dist;

	while (1) {
		dist = getDist();
		printf("dist = %0.2f cm\n", dist);
		delay(1000);
	}
	
	return 0;
}
