CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static -L.
LDLIBS = -lrobot
LIBS = -lwiringPi

robot : robot.c robot.h
	gcc -c robot.c -o robot.o $(LIBS)

librobot : robot.o
	ar rcs librobot.a robot.o
	
control : control.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	
% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)
	
all : sensor motor track avoid

clean :
	$(RM) $(EXE) *.o
