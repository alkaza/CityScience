#include "motor.h"

/* Speed */
#define SPEED	200 // possible range 0~255 PWM

int main(void)
{
	setup();
	
	setSpeed(SPEED, SPEED);
	
	while (1) {
		/* Go straight */
		setDir(FORWARD);

		/* Go back */
		//setDir(BACKWARD);
		//delay(150);
		
		/* Turn right */
		//setDir(RIGHT);
		//delay(250);
		
		/* Turn left */
		//setDir(LEFT);
		//delay(250);
		
		/* Stop */
		//setDir(STOP);
		//delay(3000);
	}

	return 0;
}
