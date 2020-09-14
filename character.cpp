#include "character.h"




std::ostream& operator<<(std::ostream& os, const character& ch) {
	os << ch.getName() << ": HP: " << ch.getCurrentHP() << ", DMG: " << ch.getAttack() << std::endl;
	return os;
}
