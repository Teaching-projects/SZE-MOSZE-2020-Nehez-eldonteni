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
	int damageDealt = opponent.takeDamage(*this);
	increaseXP(damageDealt);
}

int Adventurer::takeDamage(Character& opponent) {
	int damageTaken = 0;

	if (currentHP - opponent.getAttack() < 0) {
		damageTaken = currentHP;

		currentHP = 0;
	}
	else {
		currentHP -= opponent.getAttack();
		damageTaken = opponent.getAttack();
	}

	// check lvlup when getting attacked
	increaseXP(0);

	return damageTaken;
}