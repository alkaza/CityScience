#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

/* Min speed */
int min_speed = 60;
/* Track current flag */
volatile int turningR = 0;
volatile int turningL = 0;
volatile int goingFW = 0;
volatile int goingBW = 0;
/* Track current speed */
volatile int curr_speedA;
volatile int curr_speedB;
/* Track previous direction*/
volatile char prev_dir;

/* Setup function */
void setup(void)
{
	/* Ctrl-C handler */
	if (signal(SIGINT, sigHandler) == SIG_ERR){
		perror("Error: cannot handle SIGINT\n");
	}
	
	/* Initialize wiringPi */
	if (wiringPiSetup() == -1) {
		exit(EXIT_FAILURE);
	}

	/* Initialize ultrasonic sensor */
	ultraInit();
	/* Initialize dc motor driver */
	motorInit();
}

/* Calculate distance */
float calc_dist(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long start, stop;
	float dist;

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

	dist = (float)(stop - start) / 1000000 * 34000 / 2;
	//dist = (stop - start) * 34000 / 1000000 / 2;

	return dist;
}

/* Motor state control with gradual deceleration */
void move_slow(char dir, int speedA, int speedB)
{
	if (dir == prev_dir) {
		prev_dir = dir;
		if ((curr_speedA > min_speed) && (curr_speedB > min_speed)){
			curr_speedA-=1;
			curr_speedB-=1;
		}
		setSpeed(curr_speedA, curr_speedB);
	}
	else {	
		prev_dir = dir;
		curr_speedA = speedA;
		curr_speedB = speedB;
		setSpeed(curr_speedA, curr_speedB);
		setDir(dir);
	}
}

/* Set min speed */
void set_min_speed(int speed)
{
	min_speed = speed;
}

/* Initialize ultrasonic sensor */
void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

/* Initialize dc motor driver */
void motorInit(void) 
{
	pinMode(MotorIn1, OUTPUT);
	pinMode(MotorIn2, OUTPUT);
	pinMode(MotorIn3, OUTPUT);
	pinMode(MotorIn4, OUTPUT);
	pinMode(MotorEnA, PWM_OUTPUT);
	pinMode(MotorEnB, PWM_OUTPUT);
}

/* Set motor speed */
void setSpeed(int speedA, int speedB) 
{
	pwmWrite(MotorEnA, speedA);
	pwmWrite(MotorEnB, speedB);
}

/* Set motor direction */
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
	}
}

/* Go forward */
void goFW(void) 
{
	digitalWrite(MotorIn1, HIGH);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, HIGH);
	digitalWrite(MotorIn4, LOW);
}

/* Go backward */
void goBW(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, HIGH);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, HIGH);
}

/* Turn right */
void turnR(void) 
{
	digitalWrite(MotorIn1, HIGH);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, HIGH);
}

/* Turn left */
void turnL(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, HIGH);
	digitalWrite(MotorIn3, HIGH);
	digitalWrite(MotorIn4, LOW);
}

/* Brake */
void brake(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, LOW);
}

/* Stop */
void stop(void)
{
	setSpeed(0, 0);
}

/* Ctrl-C handler */
void sigHandler(int sigNo)
{
	printf("Caught SIGINT, exiting now\n");
	brake();
	stop();
	exit(EXIT_SUCCESS);
}
