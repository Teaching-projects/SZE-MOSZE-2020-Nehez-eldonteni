#!/bin/bash

./a.out units/halis.json units/codos.json > fight.txt
./a.out units/halis.json units/kowa.json >> fight.txt
./a.out units/codos.json units/halis.json >> fight.txt
./a.out units/codos.json units/kowa.json >> fight.txt
./a.out units/kowa.json units/halis.json >> fight.txt
./a.out units/kowa.json units/codos.json >> fight.txt

