OBJS := Character.o Adventurer.o Main.o JSONParser.o
characters := advHalis.json codos.json kowa.json

build: $(OBJS)
	g++ -Wall -Wextra -o game $(OBJS)

Main.o: Main.cpp
	g++ -Wall -Wextra -c Main.cpp

JSONParser.o: JSONParser.cpp JSONParser.h
	g++ -Wall -Wextra -c JSONParser.cpp

Character.o: Character.cpp Character.h JSONParser.h	
	g++ -Wall -Wextra -c Character.cpp

Adventurer.o: Adventurer.cpp Adventurer.h Character.h JSONParser.h
	g++ -Wall -Wextra -c Adventurer.cpp

clean:
	rm -rf *.o game ./DOCS

cppcheck:
	cppcheck *.cpp --enable=warning --error-exitcode=1
	cppcheck *.cpp --enable=warning,style,performance --output-file=testing/styleformance.txt

memcheck:
	valgrind --leak-check=full --error-exitcode=1 ./game testing/units/advHalis.json testing/units/codos.json

outputTests:
	> testing/fight.txt

	for ch1 in $(characters); do \
		for ch2 in $(characters); do \
			if [ $$ch1 != $$ch2 ]; then \
				echo $$ch1 " -> " $$ch2 && ./game testing/units/$$ch1 testing/units/$$ch2 >> testing/fight.txt; \
			fi \
		done; \
	done

	if [ "$$(diff testing/fight.txt testing/manual_calculation.txt)" = "" ]; then echo "Successful comparison! No difference between files." && exit 0; else echo "Something went wrong! There is a difference." && exit 1; fi
	

codeTests:
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make

	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	sudo ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
		
	cd testing && cmake CMakeLists.txt && make && ./runTests

doc:
	doxygen doxconf