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
#include <variant>
#include <list>

typedef std::map<std::string, std::variant<std::string, int, double>> jsonMap;

class JSON
{
public:
	JSON(jsonMap _jsonData):jsonData(_jsonData) {}
	
	typedef std::list<std::variant<std::string, int, double>> list;

	/**
	 * \brief This function reads data from file.
	 * \param fileName
	 * \return JSON object containing the key-value pairs read from the json file.
	*/
	static JSON parseFromFile(const std::string& fileName);

	/**
	 * \brief This function reads data from string.
	 * \param text
	 * \return JSON object containing the key-value pairs read from the json string.
	*/
	static JSON parseFromString(const std::string& text);

	/**
	 * \brief This function reads data from istream.
	 * \param istream
	 * \return JSON object containing the key-value pairs read from the json istream.
	*/
	static JSON parseFromStream(std::istream& stream);

	/**
	 * \class ParseException
	 * 
	 * \brief ParseException class
	*/
	class ParseException : public std::runtime_error
	{
		public:
			///This is the constructor of the class
			ParseException(const std::string& message) :std::runtime_error(message) {}
	};
	
	/**
	 * \brief This function returns if the map contains the given key.
	 * \param text
	 * \return The key found in the map (true/false).
	*/
	bool count(std::string key){
		return jsonData.count(key);
	}

	/**
	 * \brief This function returns the value of the given key.
	 * \param text
	 * \return The value paired with the given key.
	*/
	template <typename T>
	inline typename std::enable_if<!std::is_same<T, JSON::list>::value, T>::type get(std::string key) {
		if(jsonData.find(key) == jsonData.end()) {
			throw ParseException("Wrong key"); 
		}
		
		try {
			return std::get<T>(jsonData[key]);
		}
		catch(const std::exception& e) {
			throw ParseException("Wrong type"); 
		}
	}

	template <typename T>
    inline typename std::enable_if<std::is_same<T, JSON::list>::value, JSON::list>::type get(std::string key){
			if(!jsonData.count(key)){
                throw ParseException("JSON is missing a key: " + key); 
            }

            JSON::list valueList;
			
			std::string fullList = std::get<std::string>(jsonData[key]);

			unsigned int startPos = 0;
			while (startPos < fullList.length())
			{
				int commaPos = fullList.find(',', startPos);
				if (commaPos < 0)
					commaPos = fullList.length();

				std::string listMember = fullList.substr(startPos, commaPos - startPos);

				startPos = commaPos + 1;

				valueList.push_back(listMember);
			}

            return valueList;
        }

private:
	/**
	 * \brief This function removes the unnecessary white spaces and quotation marks from the string given as parameter.
	 * \param text
	*/
	static void cleanJSONWord(std::string& text);

	jsonMap jsonData; ///< The map containing the JSON data read by the class.
};

#endif