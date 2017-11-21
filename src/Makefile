CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -static
LDLIBS = -lrobot
LIBS = -lwiringPi

robot : robot.c robot.h
	gcc -c $< -o $@.o $(LIBS)

librobot : robot.o
	ar rcs $@.a $<
	
control : control.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	
all : sensor motor track avoid
	
% : %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS) $(LIBS)
	
clean :
	$(RM) $(EXE) control *.o *.a
