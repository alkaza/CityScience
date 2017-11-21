#include "robot.h"

/* Macros */
#define MINRANGE	5	// possible range 2~400 cm (3.3V)
#define SPEED		200 	// possible range 0~255 PWM

int main(void)
{
	setup();
	float range;
	setSpeed(SPEED, SPEED);

	while (1) {
		range = getRange();
		printf("range = %0.2f cm\n", range);
		delay(10);
		
		/* Modify here */
		if ((range < MINRANGE) && (range > 0)) {
    			printf("go straight\n");
			setDir(FORWARD);
		}
		else {
			printf("stop\n");
			setDir(STOP);
		}
	}

	return 0;
}
