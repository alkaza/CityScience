CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static -L.
LIBS = -lrobot

robot : robot.c robot.h
	gcc -c robot.c -o robot.o -lwiringPi

librobot : robot.o
	ar rcs librobot.a robot.o
	
% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
	
all : sensor motor track avoid control

clean :
	$(RM) $(EXE) *.o
