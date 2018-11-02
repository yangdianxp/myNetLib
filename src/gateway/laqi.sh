#!/bin/sh
killall gateway
rm logs/*.log
./gateway &
sleep 0.05
tail -f logs/*.log
