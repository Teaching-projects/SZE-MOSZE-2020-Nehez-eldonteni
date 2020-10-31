#include "Monster.h"

#include <string>

std::ostream &operator<<(std::ostream &os, const Monster &ch)
{
	os << ch.getName() << ": HP: " << ch.getHealthPoints() << ", DMG: " << ch.getDamage() << ", ATKSPEED: " << ch.getAttackCoolDown() << std::endl;
	return os;
}

Monster Monster::parse(const std::string& text) {
	JSON data = JSON::parseFromFile(text);
	
	return Monster(data.get<std::string>("name"), data.get<int>("health_points"), data.get<int>("damage"),  data.get<double>("attack_cooldown"));
}

void Monster::fightTilDeath(Monster& opponent){
	this->resetCooldown();
	opponent.resetCooldown();

	while (this->isAlive() && opponent.isAlive())
	{
		if (this->getCurrentCooldown() <= opponent.getCurrentCooldown())
		{
			this->attackEnemy(opponent);
			this->currentCooldown += this->cooldown;
		}
		else
		{
			opponent.attackEnemy(*this);
			opponent.currentCooldown += opponent.cooldown;
		}
	}
}

int Monster::attackEnemy(Monster &opponent)
{
	int damageDealt = opponent.takeDamage(*this);

	return damageDealt;
}

int Monster::takeDamage(Monster &opponent)
{
	int damageTaken = 0;

	if (currentHP - opponent.getDamage() < 0)
	{
		damageTaken = currentHP;

		currentHP = 0;
	}
	else
	{
		currentHP -= opponent.getDamage();
		damageTaken = opponent.getDamage();
	}

	return damageTaken;
}