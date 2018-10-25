#!/bin/sh
cd proto
cmake .
make
cd ..
cd common
cmake .
make
cd ..
cd base
cmake .
make
cd ..
cd client
cmake .
make
cd ..
cd central
cmake .
make
cd ..
cd gateway
cmake .
make
cd ..
cd login
cmake .
make
cd ..
cd balance
cmake .
make
cd ..
