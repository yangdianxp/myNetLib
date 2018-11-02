#!/bin/sh
killall media
rm logs/*.log
./media &
sleep 0.05
tail -f logs/*.log
