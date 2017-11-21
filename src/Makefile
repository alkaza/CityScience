all : sensor motor track avoid control

sensor : sensor.c robot.h
	gcc -I. -Wall -o sensor sensor.c -lwiringPi

motor : motor.c robot.h
	gcc -I. -Wall -o motor motor.c -lwiringPi
	
track : track.c robot.h
	gcc -I. -Wall -o track track.c -lwiringPi
	
avoid : avoid.c robot.h
	gcc -I. -Wall -o avoid avoid.c -lwiringPi

control : control.c
	gcc -I. -Wall -o control control.c -lwiringPi
	
clean :
	-rm -f sensor motor track avoid control
