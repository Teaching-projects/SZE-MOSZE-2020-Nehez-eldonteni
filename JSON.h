/**
 * \class JSON
 * 
 * \brief JSON class
 * 
 * \author AnonymDavid
 * 
 * \version 1.1
 * 
 * \date 2020/10/21 18:59
 * 
 * Created on 2020/10/21 18:59
*/
#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <any>

typedef std::map<std::string, std::any> jsonMap;

class JSON
{
public:
	JSON(jsonMap _jsonData):jsonData(_jsonData) {}

	/**
	 * \brief This function reads data from file.
	 * \param fileName
	 * \return A map with the key-value pairs read from the json file.
	*/
	static JSON parseFromFile(const std::string& fileName);

	/**
	 * \brief This function reads data from string.
	 * \param text
	 * \return A map with the key-value pairs read from the json string.
	*/
	static JSON parseFromString(const std::string& text);

	/**
	 * \brief This function reads data from istream.
	 * \param istream
	 * \return A map with the key-value pairs read from the json istream.
	*/
	static JSON parseFromStream(std::istream& stream);

	class ParseException : public std::string
	{
		public:
			///This is the constructor of the class
			ParseException(std::string message) :std::string(message) {}
	};
	
	bool count(std::string key){
		return jsonData.count(key);
	}

	template <typename T>
	T get(std::string key) {
		if(jsonData.find(key) == jsonData.end()) {
			throw ParseException("Wrong key"); 
		}
		
		try {
			return std::any_cast<T>(jsonData[key]);
		}
		catch(const std::exception& e) {
			throw ParseException("Wrong type"); 
		}
	}

private:
	/**
	 * \brief This function removes the unnecessary white spaces and quotation marks from the string given as parameter.
	 * \param text
	*/
	static void cleanJSONWord(std::string& text);

	jsonMap jsonData;
};

#endif