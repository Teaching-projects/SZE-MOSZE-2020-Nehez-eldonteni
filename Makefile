OBJS := Monster.o Hero.o Main.o JSON.o Map.o MarkedMap.o Game.o PreparedGame.o

build: $(OBJS)
	g++ -fPIC -std=c++17 -Wall -Wextra -o game $(OBJS)

Map.o: Map.cpp Map.h
	g++ -std=c++17 -Wall -Wextra -c Map.cpp

MarkedMap.o: MarkedMap.cpp MarkedMap.h Map.h
	g++ -std=c++17 -Wall -Wextra -c MarkedMap.cpp

JSON.o: JSON.cpp JSON.h
	g++ -std=c++17 -Wall -Wextra -c JSON.cpp

Monster.o: Monster.cpp Monster.h JSON.h	
	g++ -std=c++17 -Wall -Wextra -c Monster.cpp

Hero.o: Hero.cpp Hero.h Monster.h JSON.h
	g++ -std=c++17 -Wall -Wextra -c Hero.cpp

Game.o: Game.cpp Game.h Monster.h Hero.h Map.h
	g++ -std=c++17 -Wall -Wextra -c Game.cpp

PreparedGame.o: PreparedGame.cpp PreparedGame.h Game.h Monster.h Hero.h Map.h MarkedMap.h
	g++ -std=c++17 -Wall -Wextra -c PreparedGame.cpp

Main.o: Main.cpp Game.h Monster.h Hero.h JSON.h
	clang++ -fPIC -std=c++17 -Wall -Wextra -c Main.cpp


clean:
	rm -rf *.o game ./DOCS

cppcheck:
	cppcheck *.cpp --enable=warning --error-exitcode=1
	cppcheck *.cpp --enable=warning,style,performance --output-file=testing/styleformance.txt

memcheck:
	valgrind --leak-check=full --error-exitcode=1 cat testing/input1.txt | ./game preparedgame1.json

outputTests:
	> testing/fight.txt

	cat testing/input1.txt | ./game preparedgame1.json | tail -1 >> testing/fight.txt
	cat testing/input2.txt | ./game preparedgame2.json | tail -1 >> testing/fight.txt

	if [ "$$(diff testing/fight.txt testing/manual_calculation.txt)" = "" ]; then echo "Successful comparison! No difference between files." && exit 0; else echo "Something went wrong! There is a difference." && exit 1; fi

codeTests:
	cd /usr/src/gtest && cmake CMakeLists.txt && make

	ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
		
	cd testing && cmake CMakeLists.txt && make && ./runTests

doc:
	doxygen doxconf