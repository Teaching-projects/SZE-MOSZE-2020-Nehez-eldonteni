#include <iostream>
#include <string>

#include "Character.h"
#include "FileNotFoundException.h"

int main(int argc, char* argv[]) {
	int round = 0;
	bool someoneDied = false;

	try {
		Character ch1 = Character::parseUnit(argv[1]);
		Character ch2 = Character::parseUnit(argv[2]);

		do
		{
			if (round % 2 == 0)
			{
				ch1.attackEnemy(ch2);
			}
			else
			{
				ch2.attackEnemy(ch1);
			}

			if (ch1.isDead())
			{
				std::cout << ch2.getName() << " wins. Remaining HP: " << ch2.getCurrentHP() << std::endl;
				someoneDied = true;
			}
			else if (ch2.isDead())
			{
				std::cout << ch1.getName() << " wins. Remaining HP: " << ch1.getCurrentHP() << std::endl;
				someoneDied = true;
			}

			++round;

		} while (!someoneDied);
	}
	catch (FileNotFoundException ex) {
		std::cout << ex << std::endl;
		return 1;
	}

	return 0;
}
