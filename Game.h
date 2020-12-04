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
#include "Renderer.h"

class Game
{
public:
	/**
	 * \struct unit
	 * \brief unit struct
	*/
	struct unit
	{
		Monster* character; ///< The object of the unit
		int posx; ///< the x position (left to right) of the unit
		int posy; ///< the y position (top to bottom) of the unit
	};
	
	/// Default constructor for the class
	Game() :isMapSet(false), isHeroSet(false), isMonstersSet(false), isGameStarted(false), gameMap(), gameHero() {	};
	// Constructor for the class that initializes the game via marked map file
    Game(std::string mapfilename);
	// Destructor of the class
	~Game();

    /**
	 * \brief This function sets the map for the game
	 * \param map
	*/
	void setMap(Map map);
	/**
	 * \brief This function sets the wall texture for the SVG output
	 * \param filename
	*/
	void setWallTexture(std::string filename);
	/**
	 * \brief This function sets the free texture for the SVG output
	 * \param filename
	*/
	void setFreeTexture(std::string filename);
	/**
	 * \brief This function sets the map for the game with a map pointer
	 * \param map
	*/
	void setMap(Map* map);
    /**
	 * \brief This function sets the hero for the game
	 * \param hero
	 * \param x
	 * \param y
	*/
	void putHero(Hero hero, int x, int y);
    /**
	 * \brief This function sets a monster for the game
	 * \param monster
	 * \param x
	 * \param y
	*/
	void putMonster(Monster monster, int x, int y);

	/**
	 * \brief This function registers a renderer
	 * \param renderer
	*/
	virtual void registerRenderer(Renderer*);

	/**
	 * \brief This function returns the map of the game
	 * \param none
	 * \return The map
	*/
	Map* getMap() const {return gameMap;}
	/**
	 * \brief This function returns the hero of the game
	 * \param none
	 * \return The hero
	*/
	unit getHero() const {return gameHero;}
	/**
	 * \brief This function returns the wall texture of the game
	 * \param none
	 * \return The wall texture
	*/
	std::string getWallTexture() const {return wallTexture;}
	/**
	 * \brief This function returns the free texture of the game
	 * \param none
	 * \return The free texture
	*/
	std::string getFreeTexture() const {return freeTexture;}
	/**
	 * \brief This function returns every monster name and texture in the game
	 * \param none
	 * \return String vector containing every mosnters name and texture
	*/
	std::map<std::string, std::string> getEveryMonsterNameAndTexture() const;
	/**
	 * \brief This function returns the index of every monster at the given coordinates
	 * \param x
	 * \param y
	 * \return The index of every monster at the given coordinates 
	*/
	std::vector<int> getEveryMonsterIdxInPos(int x, int y) const;
	/**
	 * \brief This function returns the name of the monster at the given coordinates
	 * \param x
	 * \param y
	 * \return The name of the monster at the given coordinates 
	*/
	std::string getMonsterNameInPos(int x, int y) const;

    /**
	 * \brief This function starts the game
	 * \param none
	*/
	virtual void run();

    /**
	 * \class OccupiedException
	 * 
	 * \brief OccupiedException class
	*/
	class OccupiedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			OccupiedException(const std::string& message) :std::runtime_error(message) {}
	};

    /**
	 * \class AlreadyHasHeroException
	 * 
	 * \brief AlreadyHasHeroException class
	*/
	class AlreadyHasHeroException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			AlreadyHasHeroException(const std::string& message) :std::runtime_error(message) {}
	};

    /**
	 * \class AlreadyHasUnitsException
	 * 
	 * \brief AlreadyHasUnitsException class
	*/
	class AlreadyHasUnitsException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			AlreadyHasUnitsException(const std::string& message) :std::runtime_error(message) {}
	};

    /**
	 * \class NotInitializedException
	 * 
	 * \brief NotInitializedException class
	*/
	class NotInitializedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			NotInitializedException(const std::string& message) :std::runtime_error(message) {}
	};

    /**
	 * \class GameAlreadyStartedException
	 * 
	 * \brief GameAlreadyStartedException class
	*/
	class GameAlreadyStartedException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			GameAlreadyStartedException(const std::string& message) :std::runtime_error(message) {}
	};
	
protected:
	bool isMapSet; ///< Stores whether a map has been provided or not
	bool isHeroSet; ///< Stores whether a hero has been added or not
	bool isMonstersSet; ///< Stores whether at least one monster has been put on the map or not
	bool isGameStarted; ///< Stores whether the game has been started or not

    Map* gameMap; ///< The map in the game
    unit gameHero; ///< The hero in the game
    std::vector<unit> gameMonsters; ///< The monsters in the game
	std::string wallTexture; ///< SVG texture for walls
	std::string freeTexture; ///< SVG texture for free space
	std::vector<Renderer*> renderers; ///< Registered renderers for the program output

	/**
	 * \brief This function makes the hero fight every monster in its position
	*/
	void fightMonsters();
	/**
	 * \brief This function draw the map to the output
	*/
	void drawMap();
};

#endif