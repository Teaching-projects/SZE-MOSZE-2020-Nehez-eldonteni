#include "Monster.h"

#include <string>

std::ostream &operator<<(std::ostream &os, const Monster &ch)
{
	os << ch.getName() << ": HP: " << ch.getHealthPoints() << ", DMG (physical | magical): (" << ch.getPhysicalDamage() << " | " <<ch.getMagicalDamage() << "), ATKSPEED: " << ch.getAttackCoolDown() << std::endl;
	return os;
}

Monster Monster::parse(const std::string& text) {
	JSON data = JSON::parseFromFile(text);
	
	return Monster(data.get<std::string>("name"), data.get<int>("health_points"), data.get<int>("damage"), data.get<int>("magical_damage"),  data.get<double>("attack_cooldown"),  data.get<int>("defense"));
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

	int damageWithDefense = opponent.getPhysicalDamage() - defense;

	if (damageWithDefense <= 0)
		damageWithDefense = opponent.getMagicalDamage();
	else
		damageWithDefense += opponent.getMagicalDamage();
	

	if (currentHP - damageWithDefense < 0)
	{
		damageTaken = currentHP;

		currentHP = 0;
	}
	else
	{
		currentHP -= damageWithDefense;
		damageTaken = damageWithDefense;
	}

	return damageTaken;
}