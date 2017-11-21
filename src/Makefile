CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static -L.
LIBS = -lrobot


% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
	
all : sensor motor track avoid control

robot : robot.c robot.h
	gcc -c robot.c -o robot.o -lwiringPi

librobot : robot.o
	ar rcs librobot.a robot.o

clean :
	$(RM) $(EXE) *.o
