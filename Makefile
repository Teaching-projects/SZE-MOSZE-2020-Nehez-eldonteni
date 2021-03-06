OBJS := Monster.o Hero.o Main.o JSON.o Map.o MarkedMap.o Game.o PreparedGame.o HeroTextRenderer.o ObserverTextRenderer.o CharacterSVGRenderer.o ObserverSVGRenderer.o

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

Game.o: Game.cpp Game.h Monster.h Hero.h Map.h Renderer.h
	g++ -std=c++17 -Wall -Wextra -c Game.cpp

PreparedGame.o: PreparedGame.cpp PreparedGame.h Game.h Monster.h Hero.h Map.h MarkedMap.h JSON.h Renderer.h
	g++ -std=c++17 -Wall -Wextra -c PreparedGame.cpp

HeroTextRenderer.o: HeroTextRenderer.cpp HeroTextRenderer.h Game.h PreparedGame.h TextRenderer.h Renderer.h Hero.h Monster.h Map.h MarkedMap.h
	g++ -std=c++17 -Wall -Wextra -c HeroTextRenderer.cpp

ObserverTextRenderer.o: ObserverTextRenderer.cpp ObserverTextRenderer.h Game.h PreparedGame.h TextRenderer.h Renderer.h Hero.h Monster.h Map.h MarkedMap.h
	g++ -std=c++17 -Wall -Wextra -c ObserverTextRenderer.cpp

CharacterSVGRenderer.o: CharacterSVGRenderer.cpp CharacterSVGRenderer.h Game.h PreparedGame.h SVGRenderer.h Renderer.h Hero.h Monster.h Map.h MarkedMap.h
	g++ -std=c++17 -Wall -Wextra -c CharacterSVGRenderer.cpp

ObserverSVGRenderer.o: ObserverSVGRenderer.cpp ObserverSVGRenderer.h Game.h PreparedGame.h SVGRenderer.h Renderer.h Hero.h Monster.h Map.h MarkedMap.h
	g++ -std=c++17 -Wall -Wextra -c ObserverSVGRenderer.cpp

Main.o: Main.cpp Game.h PreparedGame.h Map.h MarkedMap.h Monster.h Hero.h JSON.h Renderer.h TextRenderer.h SVGRenderer.h HeroTextRenderer.h ObserverTextRenderer.h CharacterSVGRenderer.h ObserverSVGRenderer.h
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

	cat testing/input1.txt | ./game preparedgame1.json >> testing/fight.txt

	if [ "$$(diff testing/fight.txt testing/manual_calculation.txt)" = "" ]; then echo "Successful comparison! No difference between files." && exit 0; else echo "Something went wrong! There is a difference." && exit 1; fi

codeTests:
	cd /usr/src/gtest && cmake CMakeLists.txt && make

	ln -st /usr/lib/ /usr/src/gtest/libgtest.a
	ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
		
	cd testing && cmake CMakeLists.txt && make && ./runTests

doc:
	doxygen doxconf