#include <signal.h>
#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>
#include "robot.h"

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

void max_speed(int maxSpeed)
{
	return maxSpeed;
}

void min_speed(int minSpeed)
{
	return minSpeed;
}

void move(char dir)
{
	if (getFlag(dir)) {
		if (speed > min_speed()){
			speed-=1;
		}
		setSpeed(speed, speed);
	}
	else {	
		setFlags(dir);
		speed = max_speed();
		setDir(dir)
		setSpeed(speed, speed);
	}
}

void setFlags(char dir) 
{
	switch(dir) {
		case 'F':
			flags = {1, 0, 0, 0};
			break;
		case 'B':
			flags = {0, 1, 0, 0};
			break;
		case 'R':
			flags = {0, 0, 1, 0};
			break;
		case 'L':
			flags = {0, 0, 0, 1};
			break;
	}
}

int getFlag(char dir) 
{
	int flag;
	switch(dir) {
		case 'F':
			flag = flags[0];
			break;
		case 'B':
			flag = flags[1];
			break;
		case 'R':
			flag = flags[2];
			break;
		case 'L':
			flag = flags[3];
			break;
	}
	return flag;
}

void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
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

void brake(void) 
{
	digitalWrite(MotorIn1, LOW);
	digitalWrite(MotorIn2, LOW);
	digitalWrite(MotorIn3, LOW);
	digitalWrite(MotorIn4, LOW);
}

void stop(void)
{
	setSpeed(0, 0);
}

void sigHandler(int sigNo)
{
	printf("Caught SIGINT, exiting now\n");
	brake;
	stop;
	exit(0);
}
