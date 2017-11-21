CC = gcc
CFLAGS = -I . -Wall
LIBS = -lwiringPi

EXE : sensor motor track avoid control

all : $(EXE)

$(EXE) : $(EXE).c
        $(CC) $(CFLAGS) -o $(EXE) $(EXE).c $(LIBS)

clean :
	$(RM) $(EXE)
