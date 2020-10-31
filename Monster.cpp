#include "Character.h"
#include "FileNotFoundException.h"

#include <string>

std::ostream &operator<<(std::ostream &os, const Character &ch)
{
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << ", ATKSPEED: " << ch.getCooldown() << std::endl;
	return os;
}

Character Character::parseUnit(const std::string& text) {
	jsonMap characterData = JSONParser::parseFile(text);
	return Character(characterData["name"], std::stoi(characterData["hp"]), std::stoi(characterData["dmg"]), std::stod(characterData["attackcooldown"]));
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

int Character::attackEnemy(Character &opponent)
{
	int damageDealt = opponent.takeDamage(*this);
	this->currentCooldown += this->cooldown;

	return damageDealt;
}

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