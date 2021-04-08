#!/bin/bash
#
LENGTH=20
DELAY=1.2


while true
do
	for i in {0..20}
		do
			xdotool mousemove 510 510 click 1
		done
		sleep $DELAY
		xdotool mousemove 620 588 click 1
done
