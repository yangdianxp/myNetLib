#!/bin/sh
cd central
killall central
rm logs/*.log
./central &
cd ..
cd balance
killall balance
rm logs/*.log
./balance &
cd ..
cd login
killall login
rm logs/*.log
./login &
cd ..
cd media
killall media
rm logs/*.log
./media &
cd ..
cd gateway
killall gateway
rm logs/*.log
./gateway &
cd ..

