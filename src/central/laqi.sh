#!/bin/sh
killall central
rm logs/*.log
./central -f conf/common.json &
sleep 0.01
tail -f logs/*.log
