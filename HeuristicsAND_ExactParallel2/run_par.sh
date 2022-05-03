#!/bin/bash
RUN=5

for i in $(seq 1 $RUN)
do
  echo "RUN $i"

  echo "N=10, Threads=4"
  ./run_par grafos/grafo_10.txt 4
  echo "N=10, Threads=16"
  ./run_par grafos/grafo_10.txt 16
  echo "N=10, Threads=32"
  ./run_par grafos/grafo_10.txt 32
  echo "N=10, Threads=64"
  ./run_par grafos/grafo_10.txt 64

  echo "N=11, Threads=4"
  ./run_par grafos/grafo_11.txt 4
  echo "N=11, Threads=16"
  ./run_par grafos/grafo_11.txt 16
  echo "N=11, Threads=32"
  ./run_par grafos/grafo_11.txt 32
  echo "N=11, Threads=64"
  ./run_par grafos/grafo_11.txt 64

  echo "N=12, Threads=4"
  ./run_par grafos/grafo_12.txt 4
  echo "N=12, Threads=16"
  ./run_par grafos/grafo_12.txt 16
  echo "N=12, Threads=32"
  ./run_par grafos/grafo_12.txt 32
  echo "N=12, Threads=64"
  ./run_par grafos/grafo_12.txt 64

  echo "N=13, Threads=4"
  ./run_par grafos/grafo_13.txt 4
  echo "N=13, Threads=16"
  ./run_par grafos/grafo_13.txt 16
  echo "N=13, Threads=32"
  ./run_par grafos/grafo_13.txt 32
  echo "N=13, Threads=64"
  ./run_par grafos/grafo_13.txt 64

  echo "N=14, Threads=4"
  ./run_par grafos/grafo_14.txt 4
  echo "N=14, Threads=16"
  ./run_par grafos/grafo_14.txt 16
  echo "N=14, Threads=32"
  ./run_par grafos/grafo_14.txt 32
  echo "N=14, Threads=64"
  ./run_par grafos/grafo_14.txt 64

  echo "N=15, Threads=4"
  ./run_par grafos/grafo_15.txt 4
  echo "N=15, Threads=16"
  ./run_par grafos/grafo_15.txt 16
  echo "N=15, Threads=32"
  ./run_par grafos/grafo_15.txt 32
  echo "N=15, Threads=64"
  ./run_par grafos/grafo_15.txt 64

  echo "N=16, Threads=4"
  ./run_par grafos/grafo_16.txt 4
  echo "N=16, Threads=16"
  ./run_par grafos/grafo_16.txt 16
  echo "N=16, Threads=32"
  ./run_par grafos/grafo_16.txt 32
  echo "N=16, Threads=64"
  ./run_par grafos/grafo_16.txt 64

  echo "N=20, Threads=4"
  ./run_par grafos/grafo_20.txt 4
  echo "N=20, Threads=16"
  ./run_par grafos/grafo_20.txt 16
  echo "N=20, Threads=32"
  ./run_par grafos/grafo_20.txt 32
  echo "N=20, Threads=64"
  ./run_par grafos/grafo_20.txt 64

  echo "N=17, Threads=4"
  ./run_par grafos/grafo_17.txt 4
  echo "N=17, Threads=16"
  ./run_par grafos/grafo_17.txt 16
  echo "N=17, Threads=32"
  ./run_par grafos/grafo_17.txt 32
  echo "N=17, Threads=64"
  ./run_par grafos/grafo_17.txt 64


  echo "N=18, Threads=4"
  ./run_par grafos/grafo_18.txt 4
  echo "N=18, Threads=16"
  ./run_par grafos/grafo_18.txt 16
  echo "N=18, Threads=32"
  ./run_par grafos/grafo_18.txt 32
  echo "N=18, Threads=64"
  ./run_par grafos/grafo_18.txt 64


  echo "N=19, Threads=4"
  ./run_par grafos/grafo_19.txt 4
  echo "N=19, Threads=16"
  ./run_par grafos/grafo_19.txt 16
  echo "N=19, Threads=32"
  ./run_par grafos/grafo_19.txt 32
  echo "N=19, Threads=64"
  ./run_par grafos/grafo_19.txt 64


  echo "N=10, Threads=8"
  ./run_par grafos/grafo_10.txt 8
  echo "N=11, Threads=8"
  ./run_par grafos/grafo_11.txt 8
  echo "N=12, Threads=8"
  ./run_par grafos/grafo_12.txt 8
  echo "N=13, Threads=8"
  ./run_par grafos/grafo_13.txt 8
  echo "N=14, Threads=8"
  ./run_par grafos/grafo_14.txt 8
  echo "N=15, Threads=8"
  ./run_par grafos/grafo_15.txt 8
  echo "N=16, Threads=8"
  ./run_par grafos/grafo_16.txt 8
  echo "N=17, Threads=8"
  ./run_par grafos/grafo_17.txt 8
  echo "N=18, Threads=8"
  ./run_par grafos/grafo_18.txt 8
  echo "N=19, Threads=8"
  ./run_par grafos/grafo_19.txt 8
  echo "N=20, Threads=8"
  ./run_par grafos/grafo_20.txt 8
   
done
