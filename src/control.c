#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>

/* WiringPi pin numbering scheme */

/* motor driver pins */
#define MotorEnA	1
#define MotorIn1	2
#define MotorIn2	3

#define MotorIn3	21
#define MotorIn4	22
#define MotorEnB	23

/* ultrasonic sensor pins */
#define Trig	4
#define Echo	5

/* directions */
#define FORWARD		'F'
#define BACKWARD	'B'
#define RIGHT		'R'
#define LEFT		'L'
#define STOP		'S'

/* speed */
#define SPEED      200


void motorInit(){
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
   
   while(!(digitalRead(Echo) == 1));
   gettimeofday(&tv1, NULL);

   while(!(digitalRead(Echo) == 0));
   gettimeofday(&tv2, NULL);

   start = tv1.tv_sec * 1000000 + tv1.tv_usec;
   stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;

   range = (float)(stop - start) / 1000000 * 34000 / 2;
   //range = (stop - start) * 34000 / 1000000 / 2;

   return range;
}

/* function declarations */
void goFW();
void goBW();
void turnR();
void turnL();
void stop();
void setDir(char dir);
void setSpeed(int speedA, int speedB);
void action (char dir, int speedA, int speedB, int time);

int main(void)
{
   
   /* Setup code, it runs once */
   if (wiringPiSetup() == -1){
      return 1;
   }
   
   motorInit();
   ultraInit();
   
   float range;
   
   /* Main code, runs repeatedly: */
   while(1){
      range = getRange();
      /* Modify here: */
      if ((range < 4 )&& (range > 0)){
         action(RIGHT, SPEED, SPEED, 100);
         action(FORWARD, SPEED, SPEED, 0);
      }
      else {
         action(FORWARD, SPEED, SPEED, 0);
      }
   
   return 0;
}

void action (char dir, int speedA, int speedB, int time){
   setSpeed(0, 0);
   delay(1);
   setDir(dir);
   setSpeed(speedA, speedB);
   delay(time);
}

void setSpeed(int speedA, int speedB){
   pwmWrite (MotorEnA, speedA);
   pwmWrite (MotorEnB, speedB);
}

void setDir(char dir){
   switch (dir){
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

void goFW(){
   digitalWrite(MotorIn1, HIGH);
   digitalWrite(MotorIn2, LOW);
   digitalWrite(MotorIn3, HIGH);
   digitalWrite(MotorIn4, LOW);
}

void goBW(){
   digitalWrite(MotorIn1, LOW);
   digitalWrite(MotorIn2, HIGH);
   digitalWrite(MotorIn3, LOW);
   digitalWrite(MotorIn4, HIGH);
}

void turnR(){
   digitalWrite(MotorIn1, HIGH);
   digitalWrite(MotorIn2, LOW);
   digitalWrite(MotorIn3, LOW);
   digitalWrite(MotorIn4, HIGH);
}

void turnL(){
   digitalWrite(MotorIn1, LOW);
   digitalWrite(MotorIn2, HIGH);
   digitalWrite(MotorIn3, HIGH);
   digitalWrite(MotorIn4, LOW);
}

void stop(){
   digitalWrite(MotorIn1, LOW);
   digitalWrite(MotorIn2, LOW);
   digitalWrite(MotorIn3, LOW);
   digitalWrite(MotorIn4, LOW);
}
