#!/bin/sh
killall media
rm logs/*.log
./media -f conf/common.json &
sleep 0.01
tail -f logs/*.log
