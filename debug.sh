#!/bin/sh
if [ -z "$1"]
	then
		echo "No argument supplied"
		exit 1
fi 
gnome-terminal --geometry 70x70+1500+0 -x st-util
gnome-terminal --geometry 100x100+0+0 -x ~/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gdb -x script $1

