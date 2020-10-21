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

	virtual ~Character() {}

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
	 * \brief Simple getter function that returns the max HP of the character
	 * \param none
	 * \return The max HP of the character
	*/
	int getMaxHP() const { return maxHP; }
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
	 * \brief A function that returns a character object with the data read from a JSON file given as parameter
	 * \param fileName 
	 * \return A character object from the input 
	 * 
	 * This function provides all the data for the program to process like name, hp, dmg and cooldowns.
	*/
	static Character parseUnit(const std::string& fileName);
	

	void fight(Character& opponent);

	/// Makes the output look better
	friend std::ostream& operator<<(std::ostream & os, const Character & ch);


protected:
	const std::string name;	///< Name of the character
	int maxHP;	///< Maximum HP of the character
	int currentHP;	///< Current HP of the character
	int attack;	///< Attack damage of the character
	double cooldown;	///< Time needed between attacks of the character
	double currentCooldown;	///< Time remaining for the character's next attack

	/**
	 * \brief The fight takes place in this complex function
	 * \param opponent
	*/
	virtual int attackEnemy(Character& opponent);

	///This function substracts the opponent's attack damage from the character's HP
	int takeDamage(Character& opponent);
};

#endif
