CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -L.
LDLIBS = -lrobot
LIBS = -lwiringPi
EXE = sensor motor track avoid

#robot : robot.c robot.h
#	gcc -c $< -o $@.o $(LIBS)

#librobot : robot.o
#	ar rcs $@.a $<
	
control : control.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	
all : $(EXE)
	
% : %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS) $(LIBS)
	
clean :
	$(RM) $(EXE) control
