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

class PreparedGame : private Game
{
public:
    PreparedGame(std::string fileName) {
        loadGame(fileName);
    }

    virtual void run() { Game::run(); }

private:
    void loadGame(std::string fileName);
};

#endif