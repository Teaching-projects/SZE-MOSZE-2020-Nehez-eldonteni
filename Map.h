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
    enum type {
        Wall,
        Free
    };

    typedef std::vector<std::vector<type>> mapType;

    Map() {}
	Map(std::string filename) {
        dataMap = readFile(filename);
    }

    Map::type get(int x, int y) const;

    int getHeight() const;
    int getWidth() const;

    class WrongIndexException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			WrongIndexException(const std::string& message) :std::runtime_error(message) {}
	};
	
private:
	mapType dataMap;
    static mapType readFile(const std::string filename);
};

#endif