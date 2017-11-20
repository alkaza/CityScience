#include <signal.h>
#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>

/* WiringPi pin numbering scheme */

/* Motor driver pins */
#define MotorEnA	1
#define MotorIn1	2
#define MotorIn2	3
#define MotorIn3	21
#define MotorIn4	22
#define MotorEnB	23

/* Ultrasonic sensor pins */
#define Trig	4
#define Echo	5

/* Macros */
#define MINRANGE	5
#define SPEED		200
#define FORWARD		'F'
#define BACKWARD	'B'
#define RIGHT		'R'
#define LEFT		'L'
#define STOP		'S'

/* Function declaration */
void sigHandler	(int sigNo);
void motorInit	(void);
void ultraInit	(void);
float getRange	(void);
void setSpeed	(int speedA, int speedB);
void setDir	(char dir);
void goFW	(void);
void goBW	(void);
void turnR	(void);
void turnL	(void);
void stop	(void);

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

	motorInit();
	ultraInit();

	float range;

	/* Main code, runs repeatedly */
	while (1) {
		range = getRange();
		printf("range = %0.2f cm\n", range);
		delay(10);
		
		/* Modify here */
		if ((range < MINRANGE) && (range > 0)) {
			printf("stop\n");
			setDir(STOP);
			delay(100);
			
			printf("turn right\n");
			setDir(RIGHT);
			setSpeed(SPEED, SPEED);
		}
		else {
			printf("go straight\n");
			setDir(FORWARD);
			setSpeed(SPEED, SPEED);
		}
	}

	return 0;
}

void sigHandler(int sigNo)
{
	setDir(STOP);
	setSpeed(0, 0);
	exit(sigNo);
}

void motorInit(void) 
{
	pinMode(MotorIn1, OUTPUT);
	pinMode(MotorIn2, OUTPUT);
	pinMode(MotorIn3, OUTPUT);
	pinMode(MotorIn4, OUTPUT);
	pinMode(MotorEnA, PWM_OUTPUT);
	pinMode(MotorEnB, PWM_OUTPUT);
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

void setSpeed(int speedA, int speedB) 
{
	pwmWrite (MotorEnA, speedA);
	pwmWrite (MotorEnB, speedB);
}

void setDir(char dir) 
{
	switch (dir) {
		case 'F':
			goFW();
			break;
		case 'B':
			goBW();
			break;
		case 'R':
			turnR();
			break;
		case 'L':
			turnL();
			break;
		case 'S':
			stop();
			break;
	}
}

void goFW(void) 
{
	digitalWrite(MotorIn1, HIGH);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, HIGH);
	digitalWrite(MotorIn4, LOW);
}

void goBW(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, HIGH);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, HIGH);
}

void turnR(void) 
{
	digitalWrite(MotorIn1, HIGH);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, HIGH);
}

void turnL(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, HIGH);
	digitalWrite(MotorIn3, HIGH);
	digitalWrite(MotorIn4, LOW);
}

void stop(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, LOW);
}
