#!/bin/sh
killall balance
rm logs/*.log
./balance &
sleep 0.05
tail -f logs/*.log
