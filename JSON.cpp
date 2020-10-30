#include "JSON.h"

void JSON::cleanJSONWord(std::string& text) {
	int start = 0;

	int qMarkCount = 0;

	while (start < (int)text.length() && (text[start] == ' ' || text[start] == '\t' || text[start] == '\"' || text[start] == '{')){
		if (text[start] == '\"')
			qMarkCount++;
		start++;
	}

	int end = text.length() - 1;
	while (end >= 0 && (text[end] == ' ' || text[end] == '\t' || text[end] == '\"' || text[end] == '}')) {
		if (text[end] == '\"')
			qMarkCount++;
		end--;
	}

	if (qMarkCount % 2 != 0 || qMarkCount > 2){
		throw ParseException("Wrong JSON syntax!");
	}

	text = text.substr(start, end - start + 1);
}

JSON JSON::parseFromString(const std::string & text) {
	jsonMap characterData;

	int currentSearchPos = 0;

	int colonCount = 0;
	int commaCount = 0;
	int dataCount = 0;

	while (currentSearchPos < (int)text.length())
	{
		int colonPos = text.find(':', currentSearchPos);

		int commaPos = currentSearchPos;
		bool goodCommaPos = true;

		while (commaPos < (int)text.length() && (!goodCommaPos || text[commaPos] != ',')) {
			if (text[commaPos] == '\"')
				goodCommaPos = !goodCommaPos;

			++commaPos;
		}

		if (text[commaPos]==',')
			commaCount++;

		if (commaPos < 0)
			commaPos = text.length();

		if (colonPos >= 0) {
			colonCount++;

			std::string key = text.substr(currentSearchPos, colonPos - currentSearchPos);
			std::string value = text.substr(colonPos + 1, commaPos - (colonPos + 1));

			bool valueIsString = (value.find('\"') != std::string::npos);

			cleanJSONWord(key);
			cleanJSONWord(value);
			
			if (valueIsString)
				characterData[key] = value;
			else if (value.find('.') != std::string::npos)
				characterData[key] = std::stod(value);
			else
				characterData[key] = std::stoi(value);

			dataCount++;
		}

		currentSearchPos = commaPos + 1;
	}

	if(dataCount != colonCount || commaCount != colonCount - 1){
		throw ParseException("Wrong JSON syntax!");
	}

	return JSON(characterData);
}

JSON JSON::parseFromFile(const std::string & fileName) {
	std::ifstream ifsJSON(fileName);

	if (ifsJSON.fail())
		throw ParseException("Couldn't open file");

	std::string line;
	std::string textFromFile = "";

	while (std::getline(ifsJSON, line)) {
		textFromFile += line;
	}
	
	ifsJSON.close();
	return parseFromString(textFromFile);
}

JSON JSON::parseFromStream(std::istream & stream) {
	std::string line = "";
	std::string textFromFile = "";
	while (std::getline(stream, line)) {
		textFromFile += line;
	}

	return parseFromString(textFromFile);
}