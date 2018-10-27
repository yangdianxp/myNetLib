#!/bin/sh
killall central
rm logs/*.log
./central -f conf/common.json &
sleep 0.005
tail -f logs/*.log
