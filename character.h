#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class character
{
public:
	character(std::string _name, int _maxHP, int _attack) :name(_name), maxHP(_maxHP), currentHP(_maxHP), attack(_attack)
	{}

	~character() {}

	std::string getName() const { return name; }
	int getCurrentHP() const { return currentHP; }
	int getAttack() const { return attack; }

	bool isDead() const { return currentHP == 0; }

	void attackEnemy(character& opponent) const { opponent.takeDamage(*this); }
	void takeDamage(const character& opponent) { (currentHP - opponent.getAttack() < 0) ? currentHP = 0 : currentHP -= opponent.getAttack(); }

	friend std::ostream& operator<<(std::ostream & os, const character & ch);

private:
	const std::string name;
	const int maxHP;
	int currentHP;
	const int attack;
};

#endif
