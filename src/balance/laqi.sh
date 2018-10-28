#!/bin/sh
killall balance
rm logs/*.log
./balance -f conf/common.json &
sleep 0.01
tail -f logs/*.log
