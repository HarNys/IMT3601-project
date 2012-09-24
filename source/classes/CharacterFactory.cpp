
#include "../Includes.hpp"


CharacterFactory::CharacterFactory()
{
	int maxChar=2;
	characters.resize(maxChar);
	for (int i=0;i<maxChar;i++)
	{
		characters[i]= new Character();
	}
};


CharacterFactory CharacterFactory::*getCharacterFactory()
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