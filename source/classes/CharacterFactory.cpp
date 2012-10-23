
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
 *@param [in] 0 for LocalPlayerCharacter, 1 for NonPlayerCharacter, 3 for NetworkCharacter.
 *
 * @return on succes: pointer to a new(read: reinitialized) Character
 * 	\n on failure: NULL
 *
 * @todo fix controllers, should probably not do new every got damn time?
 */
Character* CharacterFactory::getCharacter(int controller)
{
	Character* tempCharacter;

	if (readyCharacters.size() >= 0)
	{
		tempCharacter = readyCharacters.at(readyCharacters.size()-1);
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
	if (controller == 0)
	{
		tempCharacter->mController = new LocalPlayerCharacter;
	}
	if (controller == 1)
	{
		tempCharacter->mController = new NonPlayerCharacter;
	}
	if (controller == 2)
	{
		printf("CharacterFactory::getCharacter(int): Network controllers are not implemented.\n");
	}
	return tempCharacter;
};

/**
 * releases a Character from World.
 *
 * @todo implement function!
 *
 * @return true on success.
 */
bool CharacterFactory::releaseCharacter(Character *characterReleased)
{
	printf("CharacterFactory::releaseCharacter(Character*): I DO NOTHING!\n");
	return true;
}
