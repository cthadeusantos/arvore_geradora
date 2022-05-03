#!/bin/bash
RUN=10

for i in $(seq 1 $RUN)
do
  echo "RUN $i"
  echo "N=10, Threads=4"
  
  echo "N=10, Threads=16"
  
  echo "N=10, Threads=32"
  
  echo "N=10, Threads=64"
  
done
