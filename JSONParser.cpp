#include "JSONParser.h"

void JSONParser::cleanJSONWord(std::string& text) {
	int start = 0;
	while (start < (int)text.length() && (text[start] == ' ' || text[start] == '\t' ||text[start] == '\"' || text[start] == '{'))
		start++;

	int end = text.length() - 1;;
	while (end >= 0 && (text[end] == ' ' || text[end] == '\t' || text[end] == '\"' || text[end] == '}')) 
		end--;

	text = text.substr(start, end - start + 1);
}

jsonMap JSONParser::stringParse(const std::string & text)
{
	jsonMap characterData;

	int currentSearchPos = 0;

	while (currentSearchPos < (int)text.length())
	{
		int colonPos = text.find(':', currentSearchPos);
		int commaPos = text.find(',', currentSearchPos);

		if (commaPos < 0)
			commaPos = text.length();

		if (colonPos >= 0) {
			std::string key = text.substr(currentSearchPos, colonPos - (currentSearchPos + 1));
			std::string value = text.substr(colonPos + 1, commaPos - (colonPos + 1));

			cleanJSONWord(key);
			cleanJSONWord(value);

			characterData[key] = value;
		}

		currentSearchPos = commaPos + 1;
	}

	return characterData;
}

jsonMap JSONParser::parseString(const std::string & text) {
	return stringParse(text);
}

jsonMap JSONParser::parseFile(const std::string & text) {
	std::ifstream ifsJSON(text);

	if (ifsJSON.fail())
		throw FileNotFoundException("Couldn't open file");

	std::string line;
	std::string textFromFile = "";

	while (std::getline(ifsJSON, line)) {
		textFromFile += line;
	}

	ifsJSON.close();
	return stringParse(textFromFile);
}

jsonMap JSONParser::parseStream(std::istream & stream) {
	std::string line = "";
	std::string textFromFile = "";
	while (std::getline(stream, line)) {
		textFromFile += line;
	}

	return stringParse(textFromFile);
}
