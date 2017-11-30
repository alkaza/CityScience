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
#define MotorIn3	21
#define MotorIn4	22
#define MotorEnB	23

/* Direction modes */
#define FW    'F'
#define BW    'B'
#define RIGHT 'R'
#define LEFT  'L'

/* Min speed */
extern volatile int min_speed;
/* Track current speed */
extern volatile int curr_speedA;
extern volatile int curr_speedB;
/* Track previous direction*/
extern volatile char prev_dir;

/* Setup */
extern void setup       (void);
/* Motor control */
extern void move        (char dir, int speedA, int speedB);
extern void move_slow   (char dir, int speedA, int speedB);
/* Calulate distance */
extern float calc_dist  (void);

/* Initialize */
extern void ultraInit   (void);
extern void motorInit   (void);

/* Motor functions */
extern void setSpeed    (int speedA, int speedB);
extern void setDir      (char dir);
extern void goFW        (void);
extern void goBW        (void);
extern void turnR       (void);
extern void turnL       (void);
extern void brake       (void);
extern void stop        (void);

/* Ctrl-C handler */
extern void sigHandler  (int sigNo);

#endif
