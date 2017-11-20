#include <signal.h>
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

/* WiringPi pin numbering scheme */

/* Motor driver pins */
#define MotorEnB	1
#define MotorIn4	2
#define MotorIn3	3
#define MotorIn2	21
#define MotorIn1	22
#define MotorEnA	23

/* Macros */
#define MINRANGE	5
#define SPEED		200
#define FORWARD		'F'
#define BACKWARD	'B'
#define RIGHT		'R'
#define LEFT		'L'
#define STOP		'S'

/* Function declaration */
void sigHandler (int sigNo);
void motorInit  (void);
void setSpeed   (int speedA, int speedB);
void setDir     (char dir);
void goFW       (void);
void goBW       (void);
void turnR      (void);
void turnL      (void);
void stop       (void);

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

	/* Main code, runs repeatedly */
	while (1) {
		/* Go straight */
		setDir(FORWARD);
		setSpeed(SPEED, SPEED);
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
