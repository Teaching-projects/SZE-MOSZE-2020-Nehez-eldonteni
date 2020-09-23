#!/bin/bash

> fight.txt

../a.out units/halis.json units/codos.json >> fight.txt
../a.out units/halis.json units/kowa.json >> fight.txt
../a.out units/codos.json units/halis.json >> fight.txt
../a.out units/codos.json units/kowa.json >> fight.txt
../a.out units/kowa.json units/halis.json >> fight.txt
../a.out units/kowa.json units/codos.json >> fight.txt

DIFF=$(diff fight.txt manual_calculation.txt)

if [ "$DIFF" == "" ]; then
echo "Successful comparison! No difference between files."
  exit 0
else
echo "Something went wrong! There is a difference."
  exit 1
fi
