#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <iostream>
#include <string>
#include <cmath>

#include "Character.h"
#include "FileNotFoundException.h"

class Adventurer : public Character
{
public:
	Adventurer(std::string _name, int _maxHP, int _attack) :Character(_name, _maxHP, _attack), xp(0) {}

	Adventurer(Character ch) :Character(ch.getName(), ch.getMaxHP(), ch.getAttack()), xp(0) {}

	void attackEnemy(Character& opponent);

private:
	int xp;

	int takeDamage(Character& opponent);
	void increaseXP(int xpAmmount);
};

#endif