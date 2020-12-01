/**
 * \class MarkedMap
 * 
 * \brief MarkedMap class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/11/21 13:26
 * 
 * Created on 2020/11/21 13:26
*/
#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Map.h"

class MarkedMap : public Map
{
public:
    struct unitPos
    {
        int posx;
        int posy;
        char type;
    };

    MarkedMap(const std::string filename);

    unitPos getHeroPosition() const { return hero; }

    std::vector<unitPos> getMonsterPositions(char c) const;

    std::vector<char> getMonsterChars() {return monsterChars;}

private:
    unitPos hero;
    std::vector<unitPos> monsters;
    std::vector<char> monsterChars;
};


#endif