#!/bin/sh
killall central
rm logs/*.log
./central &
sleep 0.05
tail -f logs/*.log
