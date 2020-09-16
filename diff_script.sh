#!/bin/bash

g++ -std=c++17 *.cpp
# ./a.out units/halis.json units/codos.json
#diff <(./a.out units/halis.json units/codos.json) <(cat -n dogshit.txt)
./a.out units/halis.json units/codos.json > fight.txt
./a.out units/halis.json units/kowa.json >> fight.txt
./a.out units/codos.json units/halis.json >> fight.txt
./a.out units/codos.json units/kowa.json >> fight.txt
./a.out units/kowa.json units/halis.json >> fight.txt
./a.out units/kowa.json units/codos.json >> fight.txt

DIFF=$(diff fight.txt manual_calculation.txt)

if [ "$DIFF" == "" ]; then
  echo "Successful comparison! No difference between files."
else
  echo "Something went wrong! There is a difference."
fi
