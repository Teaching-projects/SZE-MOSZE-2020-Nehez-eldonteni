#include "Adventurer.h"


void Adventurer::increaseXP(int xpAmmount)
{
	this->xp += xpAmmount;

	while (xp >= 100)
	{
		maxHP = (int)round(maxHP * 1.10);
		attack = (int)round(attack * 1.10);
		cooldown = cooldown * 0.9;
		
		currentHP = maxHP;

		xp -= 100;
	}
}

int Adventurer::attackEnemy(Character& opponent){
	int damageDealt = Character::attackEnemy(opponent);
	increaseXP(damageDealt);
	return damageDealt;
}