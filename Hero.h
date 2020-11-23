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
	Hero(std::string _name, int _maxHP, int _physicalAttack, int _magicalAttack, double _cooldown, double _defense, double _xpPerLevel, double _hpPerLevel, double _damagePerLevel, double _magicDamagePerLevel, double _cdMultiplierPerLevel, double _defenseBonusPerLevel) 
		:Monster(_name, _maxHP, _physicalAttack, _magicalAttack, _cooldown, _defense), 
		xp(0), level(1), xpPerLevel(_xpPerLevel), hpPerLevel(_hpPerLevel), damagePerLevel(_damagePerLevel), magicDamagePerLevel(_magicDamagePerLevel), cdMultiplierPerLevel(_cdMultiplierPerLevel), defensePerLevel(_defenseBonusPerLevel) {}

	/// Second constructor for the class that lets you make a Hero object from a Monster object.
	Hero(Monster ch) :Monster(ch.getName(), ch.getMaxHealthPoints(), ch.getPhysicalDamage(), ch.getMagicalDamage(), ch.getAttackCoolDown(), ch.getDefense()), 
	xp(0), level(1), xpPerLevel(0), hpPerLevel(0), damagePerLevel(0), magicDamagePerLevel(0), cdMultiplierPerLevel(0), defensePerLevel(0) {}

	/// Destruktor for the class.
	~Hero(){}
	
	/**
	 * \brief This function is an override of the parse function in the base class.
	 * \param opponent
	 * \return A Hero object from the input 
	*/
	static Hero parse(const std::string& fileName);

	/**
	 * \brief This function returns the level of the Hero.
	 * \param opponent
	 * \return The level of the hero.
	*/
	int getLevel() const { return level; }

	/**
	 * \brief This function is an override of the attackEnemy function in the base class.
	 * \param opponent
	 * \return The damage inflicted on the opponent.
	 * 
	 * This function attacks another Monster by calling the attackEnemy function in the base class with the added feature of giving this Hero the ammount of xp it inflicted on the opponent.
	*/
	virtual int attackEnemy(Monster& opponent);
private:
	int xp; ///< Experience points of the Hero
	int level; ///< Level of the Hero
	double xpPerLevel; ///< The required XP ammount needed for levelup
	double hpPerLevel; ///< Ammount of HP gain on levelup
	double damagePerLevel; ///< Ammount of physical damage gain on levelup
	double magicDamagePerLevel; ///< Ammount of magical damage gain on levelup
	double cdMultiplierPerLevel; ///< Multiplier for attack cooldown on levelup
	double defensePerLevel; ///< Multiplier for defense on levelup
	
	/**
	 * \brief This function increases the xp ammount of this object and checks for levelup. 
	 * \param opponent
	 * 
	 * In this function if the Hero reached the required ammount of xp (xpPerLevel) it levels up, raising its max hp, attack, heals to full and lowers its cooldown.
	*/
	void increaseXP(int xpAmmount);
};

#endif