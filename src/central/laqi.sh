#!/bin/sh
killall central
rm logs/*.log
./central -f conf/common.json &
sleep 1
tail -f logs/*.log
