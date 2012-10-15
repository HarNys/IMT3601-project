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
	enum characterType{npc, player};
	CharacterFactory();
	std::vector<Character *> readyCharacters;
	std::vector<Character *> usedCharacters;
public:
	Character* getCharacter(int type); ///< Gets one character for when an event is trigerd
	static CharacterFactory *getCharacterFactory(); ///< Singleton that makes sure only one character factory exists
	bool releaseCharacter(Character *characterReleased);
};



#endif // __CHARACTER__FACTORY__HEADER__GUARD__
