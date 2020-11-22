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
    enum type {
        Wall,
        Free
    };

    typedef std::vector<std::vector<type>> mapType;

public:
	Map(std::string filename) {
        dataMap = readFile(filename);
    }

    class ParseException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			ParseException(const std::string& message) :std::runtime_error(message) {}
	};
	
private:
	mapType dataMap;
    static mapType readFile(const std::string filename);
};

#endif