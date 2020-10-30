/**
 * \class Hero
 * 
 * \brief Hero class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/10/21 18:59
 * 
 * Created on 2020/10/21 18:59
*/
#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <string>
#include <cmath>

#include "Monster.h"

class Hero : public Monster
{
public:
	/// Constructor for the class that puts the input parameters into data members and passes the required variables to the base class.
	Hero(std::string _name, int _maxHP, int _attack, double _cooldown, double _xpPerLevel, double _hpPerLevel, double _damagePerLevel, double _cdMultiplierPerLevel) 
		:Monster(_name, _maxHP, _attack, _cooldown), 
		xp(0), level(1), xpPerLevel(_xpPerLevel), hpPerLevel(_hpPerLevel), damagePerLevel(_damagePerLevel), cdMultiplierPerLevel(_cdMultiplierPerLevel) {}

	/// Second constructor for the class that lets you make an Adverturer object from a Character object.
	Hero(Monster ch) :Monster(ch.getName(), ch.getMaxHealthPoints(), ch.getDamage(), ch.getAttackCoolDown()), 
	xp(0), level(1), xpPerLevel(0), hpPerLevel(0), damagePerLevel(0), cdMultiplierPerLevel(0) {}
	
	/// Destruktor for the class.
	~Hero(){}

	static Hero parse(const std::string& fileName);

	int getLevel() const { return level; }
	
	/**
	 * \brief This function is an override of the attackEnemy function in the base class.
	 * \param opponent
	 * \return The damage inflicted on the opponent.
	 * 
	 * This function attacks another character by calling the attackEnemy function in the base class with the added feature of giving this adventurer the ammount of xp it inflicted on the opponent.
	*/
	virtual int attackEnemy(Monster& opponent);

private:
	int xp;
	int level;
	double xpPerLevel;
	double hpPerLevel;
	double damagePerLevel;
	double cdMultiplierPerLevel;
	
	/**
	 * \brief This function increases the xp ammount of this object and checks for levelup. 
	 * \param opponent
	 * 
	 * In this function if the character reached the required ammount of xp (100) it levels up, raising its max hp, attack by 10%, heals to full and lowers its cooldown by 10%.
	*/
	void increaseXP(int xpAmmount);
};

#endif