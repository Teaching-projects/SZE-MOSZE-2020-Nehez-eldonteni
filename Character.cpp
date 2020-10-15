#include "Character.h"
#include "FileNotFoundException.h"

#include <string>


std::ostream& operator<<(std::ostream& os, const Character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << ", ATKSPEED: " << ch.getCooldown() << std::endl;
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
	int atk = std::stoi(line.substr(colonPos + 2, line.find_last_of(',') - (colonPos + 2)));

	// read attackcooldown
	std::getline(ifsJSON, line);
	colonPos = line.find(':');
	double as = std::stod(line.substr(colonPos + 1));

	ifsJSON.close();

	return Character(name, hp, atk, as);
}
/**
	 * \brief This function makes a character take damage from another character by subsractin damage from HP
	 * \param opponent
	 * This function is essential for the fight system of the game	 
	*/
void Character::takeDamage(Character & opponent) {
	this->currentHP -= opponent.getAttack();
}

/**
 * \brief The fight takes place in this complex function
 * \param opponent
 * 
 * In this function the characters attack each other and start their attack cooldowns. They fight until one of them reaches 0 HP and dies.
*/
void Character::attackEnemy(Character& opponent){
	opponent.takeDamage(*this);
	this->takeDamage(opponent);

	while (!(this->isDead()) && !(opponent.isDead()))
	{
		if (this->getCurrentCooldown() <= opponent.getCurrentCooldown())
		{
			opponent.takeDamage(*this);

			this->currentCooldown += this->cooldown;
		}
		else
		{
			this->takeDamage(opponent);
			
			opponent.currentCooldown += opponent.cooldown;
		}
	}
}