#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Min range */
#define MINRANGE	5 // possible range 2~400 cm (3.3V)

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
