#!/bin/bash
echo "Start"
rm -f file? file?.gz myprogram 
gcc myprogram.c -o myprogram 
echo "Step 1"; sleep 0.5;
python3 create_test_fileA.py 
echo "Step 2"; sleep 0.5;
./myprogram fileA fileB 
echo "Step 3"; sleep 0.5;
gzip -k fileA fileB 
echo "Step 4"; sleep 0.5;
gzip -cd fileB.gz | ./myprogram fileC 
echo "Step 5"; sleep 0.5;
./myprogram fileA fileD -s 100 
echo "Step 6"; sleep 0.5;
stat fileA fileA.gz fileB fileB.gz fileC fileD > result.txt 
#rm -f myprogram 
echo "Finish" 
