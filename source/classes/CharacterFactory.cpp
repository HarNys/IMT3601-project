
#include "../Includes.hpp"

CharacterFactory *CharacterFactory::characterFactory = NULL;

/** creates the factory if non exists, and makes the characters 
*   that the players and AI is going to use
*	@todo make the function take a parameter for the amount of characters to create
*/

CharacterFactory::CharacterFactory()
{
	int maxChar=2;
	Character* tempchar;
	
	characters.resize(maxChar);
	
	std::vector<Character *>::iterator cIter;

	for (cIter=characters.begin();cIter < characters.end(); cIter ++)
	{
		tempchar= new Character();
		*(cIter)=tempchar;
	}
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


/// @todo make the code fecth the character you are after not cahracter[0]
///gets one charecter for you to do some nasty things with if an event is triggered
Character* CharacterFactory::getCharacter()
{
	return characters[0];
};

/** @todo Make if statment (char type == this chartype)  like this to determin class of the player, example:
* characters[i]= new mineguy(); or characters[i]= new rifleman();
*
* Sets the characters class example, ninja, rifleman, etc.
*/

void CharacterFactory::SetCharacter(std::string type)
{
	

}