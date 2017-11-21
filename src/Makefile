CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static -L.
LIBS = -lrobot -lwiringPi

robot : robot.c robot.h
	gcc -c robot.c -o robot.o -lwiringPi

librobot : robot.o
	ar rcs librobot.a robot.o
	
control : control.c
	$(CC) $(CFLAGS) -o $@ $< -lwiringPi
	
% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
	
all : sensor motor track avoid

clean :
	$(RM) $(EXE) *.o
