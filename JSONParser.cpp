#include "JSONParser.h"

void JSONParser::cleanJSONWord(std::string& text) {
	int firstQuotMPos = text.find('"');

	if (firstQuotMPos >= 0) {
		int lastQuotMPos = text.find('"', firstQuotMPos + 1);
		text = text.substr(firstQuotMPos + 1, lastQuotMPos - (firstQuotMPos + 1));
	}
	else
	{
		int firstChar = text.find_first_not_of(' ');
		text = text.substr(firstChar, text.find_last_not_of(' ' | ',' | '}') - firstChar + 1);
	}
}

jsonMap JSONParser::stringParse(const std::string& text)
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

jsonMap JSONParser::parse(const std::string & text) {
	std::ifstream ifsJSON(text);

	if (ifsJSON.fail()) {
		if (text.find('{') < 0)
			throw FileNotFoundException("Couldn't open file");

		ifsJSON.close();
		return stringParse(text);
	}
	else
	{
		std::string line;
		std::string textFromFile = "";

		while (std::getline(ifsJSON, line)) {
			textFromFile += line;
		}
		
		ifsJSON.close();
		return stringParse(textFromFile);
	}
}

jsonMap JSONParser::parse(std::istream& stream)
{
	std::string textFromFile = "";
	std::getline(stream, textFromFile);

	return stringParse(textFromFile);
}
