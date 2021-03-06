/**
 * \class PreparedGame
 * 
 * \brief PreparedGame class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/11/21 13:26
 * 
 * Created on 2020/11/21 13:26
*/
#ifndef PREPAREDGAME_H
#define PREPAREDGAME_H

#include <iostream>

#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"
#include "Monster.h"
#include "Hero.h"
#include "Renderer.h"

class PreparedGame : private Game
{
public:
    /// Constructor for the class that initializes the game from a file
    PreparedGame(const std::string fileName) {
        loadGame(fileName);
    }

    /**
	 * \brief This function starts the game.
	*/
	virtual void run() { Game::run(); }
	/**
	 * \brief This function registers a renderer
	 * \param renderer
	*/
	virtual void registerRenderer(Renderer*);

private:
    /**
	 * \brief This function initializes the game from a file.
	 * \param fileName
	*/
	void loadGame(const std::string fileName);
};

#endif