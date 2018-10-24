#!/bin/sh
killall login
rm logs/*.log
./login -f conf/common.json &
sleep 1
tail -f logs/*.log
