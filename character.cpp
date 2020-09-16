#include "character.h"
#include "FileNotFoundException.h"

#include <string>


std::ostream& operator<<(std::ostream& os, const character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << std::endl;
	return os;
}

character character::parseUnit(std::string fileName)
{
	try
	{
		std::ifstream ifsJSON(fileName);

		if (ifsJSON.fail())
			throw FileNotFoundException("Couldn't open file");

		std::string name = "";
		int hp = 0;
		int atk = 0;

		std::string line;

		while (std::getline(ifsJSON, line))
		{
			unsigned int current = 0;

			while (current < line.length()) {
				int first = line.find("\"", current) + 1;	// first letter of key
				int last = line.find("\"", first + 1) - 1;	// last letter of key
				int end = line.find(",", current);			// end of first key-value pair
				if (end < 0)
					end = line.length();

				if (first >= 1) {

					std::string key = line.substr(first, last - first + 1);

					//getting the value (with possible quotation marks and white spaces)
					first = line.find(":", last + 2) + 1;
					last = end - 1;

					std::string value = line.substr(first, last - first + 1);	// uncleaned value

					// remove quotation marks
					first = value.find("\"");
					if (first >= 0) {
						value = value.substr(first + 1, (value.find("\"", first + 1) - 1) - (first + 1) + 1);
					}

					// remove white spaces
					first = value.find_first_not_of(' ');	// first character pos after first white space(s)
					last = value.find_last_not_of(' ');		// last character pos

					value = value.substr(first, last - first + 1);	// value

					// assign value to variables based on the key
					if (key == "name") {
						name = value;
					}
					else if (key == "hp") {
						hp = std::stoi(value);
					}
					else if (key == "dmg") {
						atk = std::stoi(value);
					}
				}

				current = end + 1;
			}
		}

		ifsJSON.close();

		return character(name, hp, atk);
	}
	catch (FileNotFoundException ex) {
		throw ex;
	}
}/*

{
  "name" : "Kakarott",
  "hp" : 30000,
  "dmg" : "9000"
}

*/