#ifndef __ROBOT_H__
#define __ROBOT_H__

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

/* Direction modes */
#define FW  'F'
#define BW  'B'
#define CW  'R'
#define CCW 'L'
#define STOP  'S'

extern void setup	(void);

extern void sigHandler (int sigNo);

extern void ultraInit	(void);
extern float getDist	(void);

extern void motorInit  (void);
extern void setSpeed   (int speedA, int speedB);
extern void setDir     (char dir);
extern void goFW       (void);
extern void goBW       (void);
extern void turnR      (void);
extern void turnL      (void);
extern void stop       (void);

#endif
