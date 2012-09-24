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
	static CharacterFactory* characterFactory;
	CharacterFactory();
	std::vector<Character *> characters;
	

public:
	Character getCharacter();						///< Gets one character for when an event is trigerd
	static CharacterFactory *getCharacterFactory(); ///< Singleton that makes sure only one character factory exists 
	void SetCharacter(std::string type);			///< sets the class for a character, example: rifleman, ninja, mine-guy


};



#endif // __CHARACTER__FACTORY__HEADER__GUARD__