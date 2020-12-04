/**
 * \class Map
 * 
 * \brief Map class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/11/21 13:26
 * 
 * Created on 2020/11/21 13:26
*/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Map
{
public:
	/** 
	 * \enum type
	 *  \brief enum type for Wall and Free blocks
	*/
    enum type {
        Wall,
        Free
    };

    typedef std::vector<std::vector<type>> mapType;

    /// Default constructor for the class
    Map() {}
    // Constructor for the class that reads a map from a file
	Map(const std::string filename);
    // Virtual destructor for polimorphism
    virtual ~Map() {}

    /**
	 * \brief Simple getter function that returns the type of a place on the map at the given coordinates
	 * \param x
     * \param y
	 * \return The type of the place on the map
	*/
	Map::type get(int x, int y) const;

    /**
	 * \brief Simple getter function that returns the height of the map
	 * \param none
	 * \return Height of the map
	*/
	int getHeight() const;
    /**
	 * \brief Simple getter function that returns the width of the map
	 * \param none
	 * \return Width of the map
	*/
	int getWidth() const;

    /**
	 * \class WrongIndexException
	 * 
	 * \brief WrongIndexException class
	*/
	class WrongIndexException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			WrongIndexException(const std::string& message) :std::runtime_error(message) {}
	};
	
protected:
	mapType dataMap; ///< Contains the map structure (walls and free space)
};

#endif