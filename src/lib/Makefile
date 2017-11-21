CC = gcc
LIBS = -lwiringPi

all : robot librobot

robot : robot.c robot.h
  $(CC) -c $< -o $@.o $(LIBS)

librobot : robot.o
  ar rcs $@.a $<
	
clean :
	$(RM) robot.o robot.a
