#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>

/* WiringPi pin numbering scheme */

/* Motor driver pins */
#define MotorEnA	1
#define MotorIn1	2
#define MotorIn2	3
#define MotorEnB	23
#define MotorIn3	22
#define MotorIn4	21

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
void move	(char dir, int speedA, int speedB);
void setSpeed   (int speedA, int speedB);
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
		move(FORWARD, SPEED, SPEED);

		/* Go back */
		//move(BACKWARD, SPEED, SPEED);
		
		/* Turn right */
		//move(RIGHT, SPEED, SPEED);
		
		/* Turn left */
		//move(LEFT, SPEED, SPEED);
		
		/* Stop */
		//move(STOP, 0, 0);
		
		//delay(3000);
	}

	return 0;
}

void sigHandler(int sigNo)
{
	move(STOP, 0, 0);
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

void move(char dir, int speedA, int speedB) 
{
	switch (dir) {
		case 'F':
			goFW();
			setSpeed(speedA, speedB);
			break;
		case 'B':
			goBW();
			setSpeed(speedA, speedB);
			delay(150);
			break;
		case 'R':
			turnR();
			setSpeed(speedA, speedB);
			delay(250);
			break;
		case 'L':
			turnL();
			setSpeed(speedA, speedB);
			delay(250);
			break;
		case 'S':
			stop();
			setSpeed(0, 0);
			delay(100);
			break;
	}
}

void setSpeed(int speedA, int speedB) 
{
	pwmWrite (MotorEnA, speedA);
	pwmWrite (MotorEnB, speedB);
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
