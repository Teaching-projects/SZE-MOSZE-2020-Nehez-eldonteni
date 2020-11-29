/**
 * \class Game
 * 
 * \brief Game class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/11/21 13:26
 * 
 * Created on 2020/11/21 13:26
*/
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include "Map.h"
#include "Hero.h"
#include "Monster.h"

class Game
{
public:
	struct unit
	{
		Monster* character;
		int posx;
		int posy;
	};
	
	Game() :isMapSet(false), isHeroSet(false), isMonstersSet(false), isGameStarted(false), gameMap(), gameHero() {	};

    Game(std::string mapfilename);
	~Game();

    void setMap(Map map);
	void setMap(Map* map);
    void putHero(Hero hero, int x, int y);
    void putMonster(Monster monster, int x, int y);

    virtual void run();

    class OccupiedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			OccupiedException(const std::string& message) :std::runtime_error(message) {}
	};

    class AlreadyHasHeroException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			AlreadyHasHeroException(const std::string& message) :std::runtime_error(message) {}
	};

    class AlreadyHasUnitsException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			AlreadyHasUnitsException(const std::string& message) :std::runtime_error(message) {}
	};

    class NotInitializedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			NotInitializedException(const std::string& message) :std::runtime_error(message) {}
	};

    class GameAlreadyStartedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			GameAlreadyStartedException(const std::string& message) :std::runtime_error(message) {}
	};
	
protected:
	bool isMapSet;
	bool isHeroSet;
	bool isMonstersSet;
	bool isGameStarted;

    Map* gameMap;
    unit gameHero;
    std::vector<unit> gameMonsters;

	std::vector<int> getEveryMonsterIdxInPos(int x, int y);
	void fightMonsters();
	void drawMap();
};

#endif