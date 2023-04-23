#!/bin/bash
make
echo "Start breaking test"
touch test.txt
echo "test test test test" > test.txt
./main test.txt -s 1 -e &
rm -f test.txt.lck

./main test.txt -s 1 -e & 
sleep 1
echo "3,1415926535" > test.txt.lck

rm -f test.txt.lck
rm -f test.txt
rm -f ./main
