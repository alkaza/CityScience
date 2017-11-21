CC = gcc
CFLAGS = -I. -Wall
LIBS = -lrobot

EXE : sensor motor track avoid control

all : $(EXE)

$(EXE) : $(EXE).c
        $(CC) $(CFLAGS) -o $(EXE) $(EXE).c $(LIBS)

robot.o : robot.c robot.h
	gcc -c robot.c -o robot.o -lwiringPi

robot : robot.o
	ar rcs librobot.a robot.o

clean :
	$(RM) $(EXE) *.o
