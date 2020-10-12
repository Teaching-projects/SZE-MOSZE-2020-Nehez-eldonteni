#include "Character.h"
#include "FileNotFoundException.h"

#include <string>


std::ostream& operator<<(std::ostream& os, const Character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << std::endl;
	return os;
}

Character Character::parseUnit(const std::string& text) {
	jsonMap characterData = JSONParser::parse(text);
	return Character(characterData["name"], std::stoi(characterData["hp"]), std::stoi(characterData["dmg"]));
}