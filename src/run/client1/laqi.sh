#!/bin/sh
killall client1
rm logs/*.log
./client1 &
sleep 0.05
tail -f logs/*.log
