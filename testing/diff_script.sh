#!/bin/bash

> testing/fight.txt

./a.out scenario1.json >> testing/fight.txt
echo "" >> testing/fight.txt
./a.out scenario2.json >> testing/fight.txt

DIFF=$(diff testing/fight.txt testing/manual_calculation.txt)
if [ "$DIFF" == "" ]; then
	echo "Successful comparison! No difference between files."
	exit 0
else
	echo "Something went wrong! There is a difference."
	exit 1
fi
