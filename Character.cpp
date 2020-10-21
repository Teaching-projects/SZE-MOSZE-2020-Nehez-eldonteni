#include "Character.h"
#include "FileNotFoundException.h"

#include <string>

std::ostream &operator<<(std::ostream &os, const Character &ch)
{
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << ", ATKSPEED: " << ch.getCooldown() << std::endl;
	return os;
}

Character Character::parseUnit(const std::string &fileName)
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

void Character::fight(Character& opponent){
	this->attackEnemy(opponent);
	opponent.attackEnemy(*this);

	while (!(this->isDead()) && !(opponent.isDead()))
	{
		if (this->getCurrentCooldown() <= opponent.getCurrentCooldown())
		{
			this->attackEnemy(opponent);
		}
		else
		{
			opponent.attackEnemy(*this);
		}
	}
}

/**
 * \brief The fight takes place in this complex function
 * \param opponent
 * 
 * In this function the characters attack each other and start their attack cooldowns. They fight until one of them reaches 0 HP and dies.
*/
int Character::attackEnemy(Character &opponent)
{
	int damageDealt = opponent.takeDamage(*this);
	this->currentCooldown += this->cooldown;

	return damageDealt;
}

/**
	 * \brief This function makes a character take damage from another character by subsractin damage from HP
	 * \param opponent
	 * This function is essential for the fight system of the game	 
	*/
int Character::takeDamage(Character &opponent)
{
	int damageTaken = 0;

	if (currentHP - opponent.getAttack() < 0)
	{
		damageTaken = currentHP;

		currentHP = 0;
	}
	else
	{
		currentHP -= opponent.getAttack();
		damageTaken = opponent.getAttack();
	}

	return damageTaken;
}