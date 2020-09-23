#!/bin/bash


> fight.txt
cd ..

 ./a.out testing/units/halis.json testing/units/codos.json >> testing/fight.txt
 ./a.out testing/units/halis.json testing/units/kowa.json >> testing/fight.txt
 ./a.out testing/units/codos.json testing/units/halis.json >> testing/fight.txt
 ./a.out testing/units/codos.json testing/units/kowa.json >> testing/fight.txt
 ./a.out testing/units/kowa.json testing/units/halis.json >> testing/fight.txt
 ./a.out testing/units/kowa.json testing/units/codos.json >> testing/fight.txt

 DIFF=$(diff testing/fight.txt testing/manual_calculation.txt)

 if [ "$DIFF" == "" ]; then
 	echo "Successful comparison! No difference between files."
 	exit 0
 else
 	echo "Something went wrong! There is a difference."
 	exit 1
 fi
