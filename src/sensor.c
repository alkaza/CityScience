#include "robot.h"

/* Min range */
#define MINRANGE	5	// possible range 2~400 cm (3.3V)

int main(void)
{
	setup();
	
	float range;

	while (1) {
		range = getRange();
		printf("range = %0.2f cm\n", range);
		delay(1000);
	}
	
	return 0;
}
