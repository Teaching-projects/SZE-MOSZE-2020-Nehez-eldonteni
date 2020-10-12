#include "Character.h"
#include "FileNotFoundException.h"

#include <string>


std::ostream& operator<<(std::ostream& os, const Character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << ", ATKSPEED: " << ch.getAttackspeed() << std::endl;
	return os;
}

/**
	 * \brief A function that returns a character object with the data read from a JSON file given as parameter
	 * \param fileName
	 * \return A character object from the input 
	 * 
	 * This function provides all the data for the program to process
	*/
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
	int atk = std::stoi(line.substr(colonPos + 2, line.find_last_of(',') - (colonPos + 2)));

	// read attackcooldown
	std::getline(ifsJSON, line);
	colonPos = line.find(':');
	double as = std::stod(line.substr(colonPos + 1));

	ifsJSON.close();

	return Character(name, hp, atk, as);
}
/**
	 * \brief This function makes a character take damage from another character(given as parameter)
	 * \param Character
	 * 
	 * This function is essential for the fight system of the game	 
	*/
void Character::takeDamage(Character & opponent) {
	opponent.currentHP -= this->getAttack();
	this->currentHP -= opponent.getAttack();

	bool thisAttackOpponent = true;

	while (!(this->isDead()) && !(opponent.isDead()))
	{
		if (thisAttackOpponent) {
			while (!(opponent.isDead()) && this->getCurrentAttackspeed() <= opponent.getCurrentAttackspeed()) {
				opponent.currentHP -= this->getAttack();

				opponent.currentAttackspeed -= this->getCurrentAttackspeed();
				this->currentAttackspeed = this->getAttackspeed();
			}
		}
		else {
			while (!(this->isDead()) && opponent.getCurrentAttackspeed() <= this->getCurrentAttackspeed()) {
				this->currentHP -= opponent.getAttack();

				this->currentAttackspeed -= opponent.getCurrentAttackspeed();
				opponent.currentAttackspeed = opponent.getAttackspeed();
			}
		}
		thisAttackOpponent = !thisAttackOpponent;
	}
}
