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
	Adventurer(std::string _name, int _maxHP, int _attack, double _cooldown) :Character(_name, _maxHP, _attack, _cooldown), xp(0) {}

	Adventurer(Character ch) :Character(ch.getName(), ch.getMaxHP(), ch.getAttack(), ch.getCooldown()), xp(0) {}
	~Adventurer(){}

	virtual int attackEnemy(Character& opponent);
	void increaseXP(int xpAmmount);
private:
	int xp;
	
};

#endif