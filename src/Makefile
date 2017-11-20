all : sensor motor control track avoid

sensor : sensor.c
	gcc -Wall -o sensor sensor.c -lwiringPi

motor : motor.c
	gcc -Wall -o motor motor.c -lwiringPi

control : control.c
	gcc -Wall -o control control.c -lwiringPi
	
track : track.c
	gcc -Wall -o track track.c -lwiringPi
	
avoid : avoid.c
	gcc -Wall -o avoid avoid.c -lwiringPi
	
clean :
	-rm -f sensor motor control track avoid
