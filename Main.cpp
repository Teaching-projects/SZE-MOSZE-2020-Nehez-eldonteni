#include <iostream>
#include <string>

#include "Character.h"
#include "Adventurer.h"
#include "FileNotFoundException.h"

/**
 * This is the main file where the action takes place
*/

int main(int argc, char* argv[]) {

	Character* ch1 = nullptr;
	Character* ch2 = nullptr;

	try {
		if (argc < 3)
			throw std::runtime_error("Not enough argument!");
		
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

		ch1->fight(*ch2);

		if (ch1->isDead())
		{
			std::cout << ch2->getName() << " wins. Remaining HP: " << ch2->getCurrentHP() << std::endl;			
		}
		else if (ch2->isDead())
		{
			std::cout << ch1->getName() << " wins. Remaining HP: " << ch1->getCurrentHP() << std::endl;
		}

		delete ch1;
		delete ch2;
	}
	catch (FileNotFoundException& ex) {
		std::cout << ex << std::endl;

		delete ch1;
		delete ch2;

		return 1;
	}catch (std::runtime_error& e)
     {
         std::cout << "Error: " << e.what() << std::endl;

		 return 1;
     }

	return 0;
}
