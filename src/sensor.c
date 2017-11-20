#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

/* WiringPi pin numbering scheme */

/* Ultrasonic sensor pins */
#define Trig	4
#define Echo	5

/* Macros */
#define MINRANGE	5

/* Function declaration */
void sigHandler	(int sigNo);
void ultraInit	(void);
float getRange	(void);

int main(void)
{
	/* Ctrl-C handler */
	if (signal(SIGINT, sigHandler) == SIG_ERR){
		printf("exit\n");
	}
	
	/* Setup code, runs once */
	if (wiringPiSetup() == -1) {
		exit(1);
	}

	ultraInit();

	float range;

	/* Main code, runs repeatedly */
	while (1) {
		range = getRange();
		printf("range = %0.2f cm\n", range);
		delay(1000);
	}

	return 0;
}

void sigHandler(int sigNo)
{
	exit(sigNo);
}

void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

float getRange(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float range;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);

	while (!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);

	while (!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	range = (float)(stop - start) / 1000000 * 34000 / 2;
	//range = (stop - start) * 34000 / 1000000 / 2;

	return range;
}
