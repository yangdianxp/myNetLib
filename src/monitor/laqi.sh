#!/bin/sh
killall monitor
rm logs/*.log
./monitor -f conf/common.json &
sleep 0.01
tail -f logs/*.log
