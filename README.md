# RPiRobot Guidelines
## Getting Started
Get source code
```
git clone https://github.com/alkaza/RPiRobot.git
```
Update repository
```
git pull
```
Go to library directory
```sh
cd /home/pi/CityScience/src/lib
```
Cleanup static library (if changes were made to static library)
```
make clean
```
Compile static library
```
make all
```
Go to source directory
```sh
cd /home/pi/CityScience/src
```
Remove static library from working directory (if changes were made to static library)
```sh
sh /home/pi/CityScience/src/scripts/rmlib.sh
examples
```
Copy static library to examples directory
```sh
sh /home/pi/CityScience/src/scripts/cplib.sh
examples
```
Go to examples directory
```sh
cd /home/pi/CityScience/src/examples
```
Cleanup all programs (if changes were made to examples)
```
make clean
```
Compile all programs
```
make all
```
Compile one program
```
make sensor
```
Run the program
```sh
sudo ./sensor
```
Terminate the program
```
Ctrl-C
```

## Tutorial
### Sample code
```c
#include <stdio.h>
#include <wiringPi.h>
#include "robot.h"

int main(void)
{
	setup();
	
	while (1) {
		/* Implement here */
	}

	return 0;
}
```
- **stdio.h** provides many standard library functions for file input and output
- **wiringPi.h** is a GPIO Interface library for the Raspberry Pi
- **robot.h** is a static library for the RPiRobot

### Setup function
```c
setup ();
```
- Must include to run once
- Allows to terminate the program with Ctrl-C
- Initializes WiringPi, ultrasonic sensor and dc motor driver 

### Infinite loop
```c
while (1) {
	/* Your code */
}
```
- Put your main code here to run repeatedly

### Calculate distance detected by ultrasonic sensor
```c
calc_dist ();
```
- **Recommended distance for obstacle avoidance**: 4~20

### Simple motor control
```c
move (direction, speedA, speedB);
```

### Motor control with gradual deceleration	
```c
move_slow (direction, speedA, speedB);
```
- **Recommended speed range**: 70~150

### Direction modes
- **FW** – go straight
- **BW** – go back
- **RIGHT** – turn right
- **LEFT** – turn left


### Advanced variables
Change until which speed to decelerate (70 by default)
```c
min_speed = speed;
```
Check the previous direction taken
```c
if (prev_dir == direction){
	/* Your code */
}
```

### Low-level motor control
Set direction
```c
setDir (direction);
```
Set speed
```c
setSpeed (speedA, speedB);
```

## Experiments
- Measuring distance
- Going forward and backward 
- Turning right and left
- Synchronizing motors
- Obstacle avoidance

**Example files** : `sensor.c motor.c motor_synch.c avoid.c avoid_alter.c` 

## Working Principles
### DC Motor Driver
  PWM (pulse width modulation) allows us to adjust the average voltage value that controls the speed of motors.
  The technique is to turn the power ON and OFF at a fast rate. The average voltage depends on the duty cycle.
  Duty cycle is the amount of time the signal is ON versus OFF in a single period of time.

  H-Bridge circuit contains four switching elements (transistors or MOSFETs), with the motor at the center.
  By activating two switches at a time we can change the direction of the current flow.
  That changes the rotation direction of the motor.

- Input1 and Input2 pins are used for controlling the rotation direction of the motor A.
- Input3 and Input4 pins are used for controlling the rotation direction of the motor B.
- EnableA and EnableB pins are used for enabling and controlling the speed of motors with PWM input.

**Possible speed range** : 0~255 PWM

| State |  EnA  |  In1  |  In2  |  In3  |  In4  |  EnB  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Stop  |   0   |   x   |   x   |   x   |   x   |   0   |
| Brake |   1   |   0   |   0   |   0   |   0   |   1   |
| BW    |   1   |   0   |   1   |   0   |   1   |   1   |
| Left  |   1   |   0   |   1   |   1   |   0   |   1   |
| Right |   1   |   1   |   0   |   0   |   1   |   1   |
| FW    |   1   |   1   |   0   |   1   |   0   |   1   |
| Brake |   1   |   1   |   1   |   1   |   1   |   1   |

### Ultrasonic Sensor
  We write HIGH to Trig (output) pin for 10 usec to generate the ultrasound.
  That sends out an 8 cycle sonic burst which will travel at the speed of sound.
  The sound wave travels to an object and bounces back.
  Echo (input) pin reads the sound wave travel time in microseconds.

- Speed of the sound = 	34000 cm/sec (or 0.034 cm/usec)
- Time = distance / speed
- Distance = time * speed / 2

**Possible distance range** : 2~400 cm (3.3V)

### Power Supplies
**Raspberry Pi 3 - Power Bank**
- Capacity : 5200mAh 
- Output : 5V 2A

**DC Motor Driver - AAx6 Battery Holder**
- Capacity : 1.5V x 6 = 9V

## Wiring Raspberry Pi 3 (Model B V1.2)
### DC Motor Driver (L296N)
|DC Motor Driver | Raspberry Pi 3 | WiringPi | Remark |
| :------------: | :------------: | :------: | :----: |
| EnA            | Physical Pin12 | Pin1     | PWM0   |
| In1            | Physical Pin13 | Pin2     |        |
| In2            | Physical Pin15 | Pin3     |        |
| In3            | Physical Pin29 | Pin21    |        |
| In4            | Physical Pin21 | Pin22    |        |
| EnB            | Physical Pin33 | Pin23    | PWM1   |
| Gnd            | Physical Pin39 |          | Ground |

**Important** : don't forget to connect Raspberry Pi GND to GND pin on the module to complete the circuit.

### Ultrasonic Sensor (HC-SR04)
| Ultrasonic Sensor | Raspberry Pi 3 | WiringPi | Remark    |
| :---------------: | :------------: | :------: | :-------: |
| Vcc               | Physical Pin1  |          | 3v3 Power |
| Trig              | Physical Pin16 | Pin4     |           |
| Echo              | Physical Pin18 | Pin5     |           |
| Gnd               | Physical Pin20 |          | Ground    |

**Important** : use Raspberry Pi 3.3V supply pin instead of 5V for the sensor signal and Raspberry Pi GPIO voltages to match.
