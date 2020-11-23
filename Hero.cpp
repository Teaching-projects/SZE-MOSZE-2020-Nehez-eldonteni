#include "Hero.h"


void Hero::increaseXP(int xpAmmount)
{
	this->xp += xpAmmount;

	while (xp >= xpPerLevel)
	{
		maxHP = (int)round(maxHP + hpPerLevel);
		attack.physical = (int)round(attack.physical + damagePerLevel);
		attack.magical = (int)round(attack.magical + magicDamagePerLevel);
		
		cooldown = cooldown * cdMultiplierPerLevel;

		defense = defense + defensePerLevel;
		
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

	return Hero(data.get<std::string>("name"), data.get<int>("base_health_points"), data.get<int>("base_damage"), data.get<int>("base_magical_damage"), data.get<double>("base_attack_cooldown"), data.get<int>("base_defense"), 
		 data.get<int>("experience_per_level"),  data.get<int>("health_point_bonus_per_level"), data.get<int>("damage_bonus_per_level"), data.get<int>("magical_damage_bonus_per_level"), data.get<double>("cooldown_multiplier_per_level"), data.get<int>("defense_bonus_per_level"));
}