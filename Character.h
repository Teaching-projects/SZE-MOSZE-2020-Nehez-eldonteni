#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <fstream>

class Character
{
public:
	Character(std::string _name, int _maxHP, int _attack) :name(_name), maxHP(_maxHP), currentHP(_maxHP), attack(_attack)
	{}

	~Character() {}

	std::string getName() const { return name; }
	int getCurrentHP() const { return currentHP; }
	int getMaxHP() const { return maxHP; }
	int getAttack() const { return attack; }

	bool isDead() const { return currentHP == 0; }

	static Character parseUnit(const std::string& name);

	virtual void attackEnemy(Character& opponent);
	int takeDamage(Character& opponent);

	friend std::ostream& operator<<(std::ostream & os, const Character & ch);

protected:
	const std::string name;
	int maxHP;
	int currentHP;
	int attack;
};

#endif
