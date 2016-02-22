#!/bin/bash
declare -a numpoints=(16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536)
for i in `seq 4 4`;
do
  if [  "$i" -ne "1"  ]
    then
      for n in `seq 0 11`;
      do
        ./randmst 0 ${numpoints[$n]} 3 $i
      done
  fi
done
