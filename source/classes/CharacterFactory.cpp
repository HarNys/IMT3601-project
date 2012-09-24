
#include "../Includes.hpp"

CharacterFactory *CharacterFactory::characterFactory = NULL;

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


///Singleton that gets the mine factory for you
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


/// @todo get the character you are after not cahracter[0]
///gets one charecter for you to do some nasty things with
Character CharacterFactory::getCharacter()
{
	return* characters[0];
};

/** @todo Make if statment (char type == this chartype)  like this to determin class of the player, example:
* characters[i]= new mineguy(); or characters[i]= new rifleman();
*/

void CharacterFactory::SetCharacter(std::string type)
{
	

}