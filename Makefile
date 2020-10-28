OBJS := Character.o Adventurer.o Main.o JSONParser.o

build: $(OBJS)
	g++ -Wall -Wextra -o game $(OBJS)

Main.o: Main.cpp
	g++ -Wall -Wextra -c Main.cpp

JSONParser.o: JSONParser.cpp
	g++ -Wall -Wextra -c JSONParser.cpp

Character.o: Character.cpp
	g++ -Wall -Wextra -c Character.cpp

Adventurer.o: Adventurer.cpp
	g++ -Wall -Wextra -c Adventurer.cpp

clean:
	rm -rf *.o game ./DOCS

cppcheck:
	cppcheck *.cpp --enable=warning --error-exitcode=1
	cppcheck *.cpp --enable=warning,style,performance --output-file=testing/styleformance.txt

valgrind:
	valgrind --leak-check=full --error-exitcode=1 ./game testing/units/advHalis.json testing/units/codos.json

outputTests:
	cd testing/ && > fight.txt

	./game testing/units/advHalis.json testing/units/codos.json >> testing/fight.txt
	./game testing/units/advHalis.json testing/units/kowa.json >> testing/fight.txt
	./game testing/units/codos.json testing/units/advHalis.json >> testing/fight.txt
	./game testing/units/codos.json testing/units/kowa.json >> testing/fight.txt
	./game testing/units/kowa.json testing/units/advHalis.json >> testing/fight.txt
	./game testing/units/kowa.json testing/units/codos.json >> testing/fight.txt

codeTests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make

	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
		
	cd testing && cmake CMakeLists.txt && make && ./runTests

doxygen:
	doxygen doxconf