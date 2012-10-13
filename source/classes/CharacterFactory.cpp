
#include "../Includes.hpp"

CharacterFactory *CharacterFactory::characterFactory = NULL;

/** creates the factory if non exists, and makes the characters
*   that the players and AI is going to use
*	@todo make the function take a parameter for the amount of characters to create
*/

CharacterFactory::CharacterFactory()
{
	int maxChar=2;
	Character* tempChar = new Character;
	tempChar->initImage();

	usedCharacters.reserve(maxChar);
	readyCharacters.assign(maxChar, new Character(*tempChar));
};

///Singleton that gets the Character Factory for you when asked for
CharacterFactory *CharacterFactory::getCharacterFactory()
{
	if (characterFactory == NULL)
	{
		characterFactory = new CharacterFactory();
		return characterFactory;
	}
	else
	{
		return characterFactory;
	}
};


/**
 * gets one charecter for you to do some nasty things with if an event is
 * triggered.
 *
 * @return on succes: pointer to a new(read: reinitialized) Character
 * 	\n on failure: NULL
 */
Character* CharacterFactory::getCharacter()
{
	Character *tempCharacter = NULL;
	if (readyCharacters.size() >= 0)
	{
		tempCharacter = readyCharacters.at(readyCharacters.size() - 1);
		usedCharacters.push_back(tempCharacter);
		readyCharacters.pop_back();
		tempCharacter->initCharacter();
	}
	else
	{
		printf("CharacterFactory::getCharacter(): Something went wrong,"
			"can not return a Character.");
		return NULL;
	}
	return tempCharacter;
};

/**
* Sets the characters class example, ninja, rifleman, etc.
*
*  @todo Make if statment (char type == this chartype)  like this to determin class of the player, example:
* characters[i]= new mineguy(); or characters[i]= new rifleman();
*/
void CharacterFactory::SetCharacter(std::string type)
{
};
