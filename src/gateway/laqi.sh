#!/bin/sh
killall gateway
rm logs/*.log
./gateway -f conf/common.json &
sleep 0.01
tail -f logs/*.log
