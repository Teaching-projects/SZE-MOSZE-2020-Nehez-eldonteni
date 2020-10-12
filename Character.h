/**
 * \class Character
 * 
 * \brief Character class
 * 
 * \author haliscsharp
 * 
 * \version 1.0
 * 
 * \date 2020/10/05 23:15
 * 
 * Created on 2020/10/05 23:15
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <fstream>

class Character
{
public:
	/// Constructor for the class that puts the input parameters into data members
	Character(std::string _name, int _maxHP, int _attack, double _attackspeed) :name(_name), maxHP(_maxHP), currentHP(_maxHP), attack(_attack), attackspeed(_attackspeed), currentAttackspeed(_attackspeed)
	{}

	/// Destructor for the class
	~Character() {}

	/// Simple getter function that returns the name of the character
	std::string getName() const { return name; }
	/// Simple getter function that returns the current HP of the character
	int getCurrentHP() const { return currentHP; }
	/// Simple getter function that returns the attack damage of the character
	int getAttack() const { return attack; }
	/// Simple getter function that returns the time needed between the character's attacks
	double getAttackspeed() const { return attackspeed; }
	/// Simple getter function that returns the time remaining for the character's next attack
	double getCurrentAttackspeed() const { return currentAttackspeed; }

	/// A function that returns if the character is dead(or not)
	bool isDead() const { return currentHP <= 0; }

	/// A function that parses a unit from a JSON source
	static Character parseUnit(const std::string& name);

	/// This functions makes a character attack another character(given as parameter) by calling it's takeDamage method
	void attackEnemy(Character& opponent) { opponent.takeDamage(*this); }

	/// Makes the output look better
	friend std::ostream& operator<<(std::ostream & os, const Character & ch);

private:
	const std::string name;	///< Name of the character
	const int maxHP;	///< Maximum HP of the character
	int currentHP;	///< Current HP of the character
	const int attack;	///< Attack damage of the character
	const double attackspeed;	///< Time needed between attacks of the character
	double currentAttackspeed;	///< Time remaining for the character's next attack

	///This function makes a character take damage from another character(given as parameter)
	void takeDamage(Character& opponent);
};

#endif
