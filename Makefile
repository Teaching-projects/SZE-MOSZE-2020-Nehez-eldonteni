OBJS := Monster.o Hero.o Main.o JSON.o

build: $(OBJS)
	g++ -fPIC -std=c++17 -Wall -Wextra -o game $(OBJS)

Main.o: Main.cpp
	clang++ -fPIC -std=c++17 -Wall -Wextra -c Main.cpp

JSON.o: JSON.cpp JSON.h
	g++ -std=c++17 -Wall -Wextra -c JSON.cpp

Monster.o: Monster.cpp Monster.h JSON.h	
	g++ -std=c++17 -Wall -Wextra -c Monster.cpp

Hero.o: Hero.cpp Hero.h Monster.h JSON.h
	g++ -std=c++17 -Wall -Wextra -c Hero.cpp

clean:
	rm -rf *.o game ./DOCS

cppcheck:
	cppcheck *.cpp --enable=warning --error-exitcode=1
	cppcheck *.cpp --enable=warning,style,performance --output-file=testing/styleformance.txt

memcheck:
	valgrind --leak-check=full --error-exitcode=1 ./game scenario1.json

outputTests:
	> testing/fight.txt

	./a.out scenario1.json >> testing/fight.txt
	echo "" >> testing/fight.txt
	./a.out scenario2.json >> testing/fight.txt

	if [ "$$(diff testing/fight.txt testing/manual_calculation.txt)" = "" ]; then echo "Successful comparison! No difference between files." && exit 0; else echo "Something went wrong! There is a difference." && exit 1; fi

codeTests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make

	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
		
	cd testing && cmake CMakeLists.txt && make && ./runTests

doc:
	doxygen doxconf