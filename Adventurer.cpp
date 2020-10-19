#include "Adventurer.h"


void Adventurer::increaseXP(int xpAmmount)
{
	this->xp += xpAmmount;

	while (xp >= 100)
	{
		maxHP = (int)round(maxHP * 1.10);
		attack = (int)round(attack * 1.10);

		currentHP = maxHP;

		xp -= 100;
	}
}

void Adventurer::attackEnemy(Character& opponent){
	int damageDealt = Character::attackEnemy(*this);
	this->currentCooldown += this->cooldown;
	increaseXP(damageDealt);
}