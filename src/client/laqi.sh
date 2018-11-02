#!/bin/sh
killall client
rm logs/*.log
./client &
sleep 0.05
tail -f logs/*.log
