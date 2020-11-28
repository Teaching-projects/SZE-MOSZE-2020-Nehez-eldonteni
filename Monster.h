/**
 * \class Monster
 * 
 * \brief Monster class
 * 
 * \author haliscsharp
 * 
 * \version 1.0
 * 
 * \date 2020/10/05 23:15
 * 
 * Created on 2020/10/05 23:15
*/

#ifndef MONSTER_H
#define MONSTER_H

#include "JSON.h"

#include <iostream>
#include <fstream>

class Monster
{
public:
	/// Constructor for the class that puts the input parameters into data members
	Monster(std::string _name, int _maxHP, int _physicalAttack, int _magicalAttack, double _cooldown, double _defense) :name(_name), maxHP(_maxHP), currentHP(_maxHP), attack({_physicalAttack, _magicalAttack}), cooldown(_cooldown), currentCooldown(_cooldown), defense(_defense)
	{}
	/// Virtual destructor for the class
	virtual ~Monster() {}

	/**
	 * \brief Simple getter function that returns the name of the Monster
	 * \param none
	 * \return The name of the Monster
	*/
	std::string getName() const { return name; }
	/**
	 * \brief Simple getter function that returns the current HP of the Monster
	 * \param none
	 * \return The current HP of the Monster
	*/
	int getHealthPoints() const { return currentHP; }
	/**
	 * \brief Simple getter function that returns the max HP of the Monster
	 * \param none
	 * \return The max HP of the Monster
	*/
	int getMaxHealthPoints() const { return maxHP; }
	/**
	 * \brief Simple getter function that returns the physical damage of the Monster
	 * \param none
	 * \return The physical damage of the Monster
	*/
	int getPhysicalDamage() const { return attack.physical; }
	/**
	 * \brief Simple getter function that returns the magical damage of the Monster
	 * \param none
	 * \return The magical damage of the Monster
	*/
	int getMagicalDamage() const { return attack.magical; }
	/**
	 * \brief Simple getter function that returns the time needed between the Monster's attacks
	 * \param none
	 * \return The cooldown of the Monster
	*/
	double getAttackCoolDown() const { return cooldown; }
	/**
	 * \brief Simple getter function that returns the time needed for the Monster's next attack
	 * \param none
	 * \return The current remaining cooldown of the Monster
	*/
	double getCurrentCooldown() const { return currentCooldown; }
	/**
	 * \brief Simple getter function that returns the the damage the Monster can absorb in an attack
	 * \param none
	 * \return The defense value of the Monster
	*/
	double getDefense() const { return defense; }

	/**
	 * \brief This function resets the attack cooldown of the monster
	 * \param none
	*/
	void resetCooldown() {
		currentCooldown = cooldown;
	}

	/**
	 * \brief This function returns if either a Monster is alive or dead
	 * \param none
	 * \return True or false value based on the Monster's state(alive or dead)
	*/
	bool isAlive() const { return currentHP > 0; }

	/**
	 * \brief A function that returns a Monster object with the data read from a JSON file given as parameter
	 * \param fileName 
	 * \return A Monster object from the input 
	 * 
	 * This function provides all the data for the program to process like name, hp, dmg and cooldowns.
	*/
	static Monster parse(const std::string& fileName);
	
	/**
	 * \brief The fight takes place in this complex function
	 * \param opponent
	 * 
	 * In this function the Monsters attack each other and start their attack cooldowns. They fight until one of them reaches 0 HP and dies.
	*/
	void fightTilDeath(Monster& opponent);
	
	/**
	 * \brief This function attacks another Monster.
	 * \param opponent
	 * \return The damage inflicted on the opponent.
	*/
	virtual int attackEnemy(Monster& opponent);

	/// Makes the output look better
	friend std::ostream& operator<<(std::ostream & os, const Monster & ch);


protected:
	struct Damage {
		int physical;
		int magical;

		Damage operator+(const Damage& other){
			Damage tempDmg;
			
			tempDmg.physical = this->physical + other.physical;
			tempDmg.magical = this->magical + other.magical;

			return tempDmg;
        }

		Damage& operator+=(const Damage& other){
			this->physical += other.physical;
			this->magical += other.magical;

			return *this;
		}

		Damage& operator*=(const Damage& other){
			this->physical *= other.physical;
			this->magical *= other.magical;
			
			return *this;
		}
	};

	const std::string name;	///< Name of the Monster
	int maxHP;	///< Maximum HP of the Monster
	int currentHP;	///< Current HP of the Monster
	Damage attack;	///< Attack damage of the Monster
	double cooldown;	///< Time needed between attacks of the Monster
	double currentCooldown;	///< Time remaining for the Monster's next attack
	int defense; ///< The amount of damage the Monster can absorb

	/**
	 * \brief This function makes a Monster take damage from another Monster by subsracting damage from HP
	 * \param opponent
	 * This function is essential for the fight system of the game	 
	*/
	int takeDamage(Monster& opponent);
};

#endif
