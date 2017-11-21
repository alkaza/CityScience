CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static -L.
LIBS = -lrobot

EXE : sensor motor track avoid control

all : $(EXE)

$(EXE) : $(EXE).c
        $(CC) $(CFLAGS) -o $(EXE) $(EXE).c $(LDFLAGS) $(LIBS)

robot.o : robot.c robot.h
	gcc -c robot.c -o robot.o -lwiringPi

librobot.a : robot.o
	ar rcs librobot.a robot.o

clean :
	$(RM) $(EXE) *.o
