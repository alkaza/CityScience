CC = gcc
CFLAGS = -I. -Wall
LDFLAGS = -L.
LDLIBS = -lrobot
LIBS = -lwiringPi
EXE = sensor motor synch avoid
	
all : $(EXE)
	
% : %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS) $(LIBS)
	
clean :
	$(RM) $(EXE)
