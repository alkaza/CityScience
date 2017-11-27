#!/bin/sh
echo -en "Remove lib from... "
read SRCD
rm $SRCD/robot.h $SRCD/librobot.a
