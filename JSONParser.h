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
	/**
	 * \brief This function reads data from file.
	 * \param fileName
	 * \return A map with the key-value pairs read from the json file.
	*/
	static jsonMap parseFile(const std::string& fileName);

	/**
	 * \brief This function reads data from string.
	 * \param text
	 * \return A map with the key-value pairs read from the json string.
	*/
	static jsonMap parseString(const std::string& text);

	/**
	 * \brief This function reads data from istream.
	 * \param istream
	 * \return A map with the key-value pairs read from the json istream.
	*/
	static jsonMap parseStream(std::istream& stream);

private:
	/**
	 * \brief This function removes the unnecessary white spaces and quotation marks from the string given as parameter.
	 * \param text
	*/
	static void cleanJSONWord(std::string& text);
};

#endif