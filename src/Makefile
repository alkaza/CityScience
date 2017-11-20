all : sensor motor control

sensor : sensor.c
  gcc -Wall -o sensor sensor.c -lwiringPi

motor : motor.c
  gcc -Wall -o motor motor.c -lwiringPi

control : control.c
  gcc -Wall -o control control.c -lwiringPi

clean :
  -rm -f sensor motor control
