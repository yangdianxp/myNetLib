#!/bin/sh
cd proto
cmake .
make clean
make
cd ..
cd common
cmake .
make clean
make
cd ..
cd base
cmake .
make clean
make
cd ..
cd client
cmake .
make clean
make
cd ..
cd central
cmake .
make clean
make
cd ..
cd gateway
cmake .
make clean
make 
cd ..
cd login
cmake .
make clean
make 
cd ..
