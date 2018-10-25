#!/bin/sh
killall balance
rm logs/*.log
./balance -f conf/common.json &
sleep 1
tail -f logs/*.log
