#!/bin/sh
LIBD="/home/pi/RPiRobot/src/lib"
echo -en "Copy lib to... "
read SRCD 
echo $SRCD
cp $LIBD/robot.h $LIBD/librobot.a $SRCD
