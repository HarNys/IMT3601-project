#ifndef __CHARACTER__FACTORY__HEADER__GUARD__
#define __CHARACTER__FACTORY__HEADER__GUARD__

#include "../Includes.hpp"

/**
* @brief Character factory that holds the characters in the game
* @todo Make the clase take parameters from console
* @todo Add resize function
*/

class CharacterFactory
{
private:
	CharacterFactory();
	std::vector<Character *> characters;

public:
	CharacterFactory getCharacter();
	static CharacterFactory *getCharacterFactory();


};



#endif // __CHARACTER__FACTORY__HEADER__GUARD__