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
    /**
     * \struct unitPos
     * \brief unit position
    */
    struct unitPos
    {
        int posx; ///< x coordinate of the unit
        int posy; ///< y coordinate of the unit
        char type; ///< identification for the unit
    };

    /// Constructor for the class that reads a marked map from the given file
	MarkedMap(const std::string filename);

    /**
	 * \brief Getter function that returns the position of the hero
	 * \param none
     * \return The position of the hero
	*/
	unitPos getHeroPosition() const { return hero; }

    /**
	 * \brief Getter function that returns the position of the monsters that have the type given as parameter
	 * \param c
     * \return The position of the monsters
	*/
	std::vector<unitPos> getMonsterPositions(char c) const;

    /**
	 * \brief Getter function that returns every type of the monsters on the map
	 * \param none
     * \return The type of the monsters
	*/
	std::vector<char> getMonsterChars() const {return monsterChars;}

private:
    unitPos hero; ///< Position of the hero
    std::vector<unitPos> monsters; ///< Position and type (id) of every monster
    std::vector<char> monsterChars; ///< Type (id) of every monster
};


#endif