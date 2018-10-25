#!/bin/sh
killall media
rm logs/*.log
./media -f conf/common.json &
sleep 1
tail -f logs/*.log
