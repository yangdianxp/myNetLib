#!/bin/sh
cd balance
killall balance
rm logs/*.log
./balance -f conf/common.json &
cd ..
cd login
killall login
rm logs/*.log
./login -f conf/common.json &
cd ..
cd media
killall media
rm logs/*.log
./media -f conf/common.json &
cd ..
cd gateway
killall gateway
rm logs/*.log
./gateway -f conf/common.json &
cd ..

