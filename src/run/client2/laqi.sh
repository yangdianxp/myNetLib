#!/bin/sh
killall client2
rm logs/*.log
./client2 &
sleep 0.05
tail -f logs/*.log
