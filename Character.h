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
	Character(std::string _name, int _maxHP, int _attack, double _cooldown) :name(_name), maxHP(_maxHP), currentHP(_maxHP), attack(_attack), cooldown(_cooldown), currentCooldown(_cooldown)
	{}

	/// Destructor for the class
	~Character() {}

	/**
	 * \brief Simple getter function that returns the name of the character
	 * \param none
	 * \return The name of the character
	*/
	std::string getName() const { return name; }
	/**
	 * \brief Simple getter function that returns the current HP of the character
	 * \param none
	 * \return The current HP of the character
	*/
	int getCurrentHP() const { return currentHP; }
	/**
	 * \brief Simple getter function that returns the attack damage of the character
	 * \param none
	 * \return The attack damage of the character
	*/
	int getAttack() const { return attack; }
	/**
	 * \brief Simple getter function that returns the time needed between the character's attacks
	 * \param none
	 * \return The cooldown of the character
	*/
	double getCooldown() const { return cooldown; }
	/**
	 * \brief Simple getter function that returns the time needed for the character's next attack
	 * \param none
	 * \return The current remaining cooldown of the character
	*/
	double getCurrentCooldown() const { return currentCooldown; }

	/**
	 * \brief This function returns if either a character is dead or not
	 * \param none
	 * \return True or false value based on the character's state(dead or not)
	*/
	bool isDead() const { return currentHP <= 0; }

	/**
	 * \brief Essential function that makes the character parsing possible
	 * \param name
	 * \return This function returns a character object
	*/
	static Character parseUnit(const std::string& name);

	
	/**
	 * \brief The fight takes place in this complex function
	 * \param opponent
	*/
	void attackEnemy(Character& opponent);

	/// Makes the output look better
	friend std::ostream& operator<<(std::ostream & os, const Character & ch);

private:
	const std::string name;	///< Name of the character
	const int maxHP;	///< Maximum HP of the character
	int currentHP;	///< Current HP of the character
	const int attack;	///< Attack damage of the character
	const double cooldown;	///< Time needed between attacks of the character
	double currentCooldown;	///< Time remaining for the character's next attack

	///This function substracts the opponent's attack damage from the character's HP
	void takeDamage(Character& opponent);
};

#endif
