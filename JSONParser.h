/**
 * \class JSONParser
 * 
 * \brief JSONParser class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/10/21 18:59
 * 
 * Created on 2020/10/21 18:59
*/
#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "FileNotFoundException.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

typedef std::map<std::string, std::string> jsonMap;

class JSONParser
{
public:
	static jsonMap parseFile(const std::string& text);
	static jsonMap parseString(const std::string& text);
	static jsonMap parseStream(std::istream& stream);

private:
	static void cleanJSONWord(std::string& text);
};

#endif