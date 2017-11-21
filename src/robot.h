#ifndef __ROBOT_H__
#define __ROBOT_H__
#include <signal.h>
#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

/* WiringPi pin numbering scheme */
/* Ultrasonic sensor pins */
#define Trig	4
#define Echo	5

/* Motor driver pins */
/* Motor A */
#define MotorEnA	1
#define MotorIn1	2
#define MotorIn2	3
/* Motor B */
#define MotorEnB	23
#define MotorIn3	22
#define MotorIn4	21

/* Directions */
#define FORWARD		'F'
#define BACKWARD	'B'
#define RIGHT		'R'
#define LEFT		'L'
#define STOP		'S'

/* Function declarations */
void setup	(void);
void sigHandler (int sigNo);
void ultraInit	(void);
float getRange	(void);
void motorInit  (void);
void setSpeed   (int speedA, int speedB);
void setDir     (char dir);
void goFW       (void);
void goBW       (void);
void turnR      (void);
void turnL      (void);
void stop       (void);

void setup(void)
{
	/* Ctrl-C handler */
	if (signal(SIGINT, sigHandler) == SIG_ERR){
		perror("Error: cannot handle SIGINT\n");
	}
	
	if (wiringPiSetup() == -1) {
		exit(1);
	}

	ultraInit();
	motorInit();
}

void sigHandler(int sigNo)
{
	printf("Caught SIGINT, exiting now\n");
	setDir(STOP);
	setSpeed(0, 0);
	exit(0);
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

void motorInit(void) 
{
	pinMode(MotorIn1, OUTPUT);
	pinMode(MotorIn2, OUTPUT);
	pinMode(MotorIn3, OUTPUT);
	pinMode(MotorIn4, OUTPUT);
	pinMode(MotorEnA, PWM_OUTPUT);
	pinMode(MotorEnB, PWM_OUTPUT);
}

void setSpeed(int speedA, int speedB) 
{
	pwmWrite(MotorEnA, speedA);
	pwmWrite(MotorEnB, speedB);
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

#endif
