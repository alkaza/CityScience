CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -L.
LDLIBS = -lrobot
LIBS = -lwiringPi
EXE = sensor motor motor_synch avoid avoid_alter
	
all : $(EXE)
	
% : %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS) $(LIBS)
	
clean :
	$(RM) $(EXE)
