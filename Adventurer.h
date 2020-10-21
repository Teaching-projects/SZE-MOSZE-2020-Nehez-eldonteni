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
	/// Constructor for the class that puts the input parameters into data members and passes the required variables to the base class.
	Adventurer(std::string _name, int _maxHP, int _attack, double _cooldown) :Character(_name, _maxHP, _attack, _cooldown), xp(0) {}
	/// Second constructor for the class that lets you make an Adverturer object from a Character object.
	Adventurer(Character ch) :Character(ch.getName(), ch.getMaxHP(), ch.getAttack(), ch.getCooldown()), xp(0) {}
	/// Destruktor for the class.
	~Adventurer(){}
	
	/**
	 * \brief This function is an override of the attackEnemy function in the base class.
	 * \param opponent
	 * \return The damage inflicted on the opponent.
	 * 
	 * This function attacks another character by calling the attackEnemy function in the base class with the added feature of giving this adventurer the ammount of xp it inflicted on the opponent.
	*/
	virtual int attackEnemy(Character& opponent);
private:
	int xp;
	
	/**
	 * \brief This function increases the xp ammount of this object and checks for levelup. 
	 * \param opponent
	 * 
	 * In this function if the character reached the required ammount of xp (100) it levels up, raising its max hp, attack by 10%, heals to full and lowers its cooldown by 10%.
	*/
	void increaseXP(int xpAmmount);
};

#endif