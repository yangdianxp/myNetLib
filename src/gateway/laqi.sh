#!/bin/sh
killall gateway
rm logs/*.log
./gateway -f conf/common.json &
sleep 1
tail -f logs/*.log
