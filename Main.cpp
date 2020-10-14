#include <iostream>
#include <string>

#include "Character.h"
#include "Adventurer.h"
#include "FileNotFoundException.h"

int main(int argc, char* argv[]) {
	int round = 0;
	bool someoneDied = false;

	Character* ch1;
	Character* ch2;

	try {

		std::string sCh1 = argv[1];
		std::string sCh2 = argv[2];

		if (sCh1.substr(sCh1.find_last_of('/') + 1, 3) == "adv") {
			ch1 = new Adventurer(Character::parseUnit(sCh1));
		}
		else {
			ch1 = new Character(Character::parseUnit(sCh1));
		}

		if (sCh2.substr(sCh2.find_last_of('/') + 1, 3) == "adv") {
			ch2 = new Adventurer(Adventurer::parseUnit(sCh2));
		}
		else {
			ch2 = new Character(Character::parseUnit(sCh2));
		}

		do
		{
			if (round % 2 == 0)
			{
				ch1->attackEnemy(*ch2);
			}
			else
			{
				ch2->attackEnemy(*ch1);
			}

			if (ch1->isDead())
			{
				std::cout << ch2->getName() << " wins. Remaining HP: " << ch2->getCurrentHP() << std::endl;
				someoneDied = true;
			}
			else if (ch2->isDead())
			{
				std::cout << ch1->getName() << " wins. Remaining HP: " << ch1->getCurrentHP() << std::endl;
				someoneDied = true;
			}

			++round;

		} while (!someoneDied);
	}
	catch (FileNotFoundException ex) {
		std::cout << ex << std::endl;
		return 1;
	}

	delete ch1;
	delete ch2;

	return 0;
}
