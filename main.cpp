#include <iostream>
#include <string>
 
#include "character.h"

int main(int argc, char* argv[]) {
	int round = 0;
	bool someoneDied = false;

	character* ch1 = new character(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	character* ch2 = new character(argv[4], std::stoi(argv[5]), std::stoi(argv[6]));

	//character ch1("Maple", 150, 10);
	//character ch2("Sally", 45, 30);

	std::cout << *ch1 << *ch2 << std::endl;

	do
	{
		if (round % 2 == 0)
		{
			std::cout << ch1->getName() << " -> " << ch2->getName() << std::endl;

			ch1->attackEnemy(ch2);
		}
		else
		{
			std::cout << ch2->getName() << " -> " << ch1->getName() << std::endl;

			ch2->attackEnemy(ch1);
		}

		std::cout << *ch1 << *ch2 << std::endl;

		if (ch1->isDead())
		{
			std::cout << ch1->getName() << " died. " << ch2->getName() << " wins." << std::endl;
			someoneDied = true;
		}
		else if (ch2->isDead())
		{
			std::cout << ch2->getName() << " died. " << ch1->getName() << " wins." << std::endl;
			someoneDied = true;
		}

		++round;

	} while (!someoneDied);

	delete ch1;
	delete ch2;


}
