#!/bin/sh
echo -en "Remove lib from... "
read SRCD
echo $SRCD
rm $SRCD/robot.h #SRCD/librobot.a
