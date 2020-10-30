#include "Hero.h"


void Hero::increaseXP(int xpAmmount)
{
	this->xp += xpAmmount;

	while (xp >= xpPerLevel)
	{
		maxHP = (int)round(maxHP + hpPerLevel);
		attack = (int)round(attack + damagePerLevel);
		
		cooldown = cooldown * cdMultiplierPerLevel;

		currentHP = maxHP;

		xp -= xpPerLevel;

		level++;
	}
}

int Hero::attackEnemy(Monster& opponent){
	int damageDealt = Monster::attackEnemy(opponent);
	increaseXP(damageDealt);
	return damageDealt;
}

Hero Hero::parse(const std::string& fileName){
	JSON data = JSON::parseFromFile(fileName);

	return Hero(data.get<std::string>("name"), data.get<int>("base_health_points"), data.get<int>("base_damage"),  data.get<double>("base_attack_cooldown"), 
		 data.get<int>("experience_per_level"),  data.get<int>("health_point_bonus_per_level"),  data.get<int>("damage_bonus_per_level"),  data.get<double>("cooldown_multiplier_per_level"));
}