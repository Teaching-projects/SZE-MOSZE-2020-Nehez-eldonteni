#include "Character.h"
#include "FileNotFoundException.h"

#include <string>


std::ostream& operator<<(std::ostream& os, const Character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << std::endl;
	return os;
}

Character Character::parseUnit(const std::string& fileName)
{
	std::ifstream ifsJSON(fileName);

	if (ifsJSON.fail())
		throw FileNotFoundException("Couldn't open file");

	std::string line;

	std::getline(ifsJSON, line);

	// read name
	std::getline(ifsJSON, line);
	int colonPos = line.find(':');
	std::string name = line.substr(colonPos + 3, line.find_last_of('"') - (colonPos + 3));

	// read hp
	std::getline(ifsJSON, line);
	colonPos = line.find(':');
	int hp = std::stoi(line.substr(colonPos + 2, line.find_last_of(',') - (colonPos + 2)));

	// read dmg
	std::getline(ifsJSON, line);
	colonPos = line.find(':');
	int atk = std::stoi(line.substr(colonPos + 1));

	ifsJSON.close();

	return Character(name, hp, atk);
}

void Character::attackEnemy(Character & opponent) {
	opponent.takeDamage(*this);
}

int Character::takeDamage(Character & opponent) {
	int damageTaken = 0;

	if (currentHP - opponent.getAttack() < 0) {
		damageTaken = currentHP;

		currentHP = 0;
	}
	else {
		currentHP -= opponent.getAttack();
		damageTaken = opponent.getAttack();
	}

	return damageTaken;
}
