#!/bin/sh
killall client3
rm logs/*.log
./client3 &
sleep 0.05
tail -f logs/*.log
