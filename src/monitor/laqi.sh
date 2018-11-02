#!/bin/sh
killall monitor
rm logs/*.log
./monitor &
sleep 0.05
tail -f logs/*.log
