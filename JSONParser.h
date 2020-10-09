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
	static jsonMap parse(const std::string& text);
	static jsonMap parse(std::istream& stream);

private:
	static void cleanJSONWord(std::string& text);
	static jsonMap stringParse(const std::string& text);
};

#endif