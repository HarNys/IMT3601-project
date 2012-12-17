/*
 * CharacterFactory.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thoams.sigurdsen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "../Includes.hpp"

CharacterFactory *CharacterFactory::characterFactory = NULL;

/** creates the factory if non exists, and makes the characters
*   that the players and AI is going to use
*	@todo make the function take a parameter for the amount of characters to create
*/

CharacterFactory::CharacterFactory()
{

	int maxChar=10;
	Character* tempChar = new Character();
	tempChar->initImage();

	usedCharacters.reserve(maxChar);
	readyCharacters.reserve(maxChar);
	//readyCharacters.assign(maxChar, new Character);
	for (int i = 0; i < maxChar; i ++)
	{
		tempChar = new Character();
		readyCharacters.push_back(tempChar);
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


/**
 * gets one charecter for you to do some nasty things with if an event is
 * triggered.
 *
 * @return on succes: pointer to a new(read: reinitialized) Character
 * 	\n on failure: NULL
 */
Character* CharacterFactory::getCharacter()
{
//	characterType typeOfplayer;

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
	return tempCharacter;
};

/**
 * releases a Character from World.
 *
 * @todo implement function!
 *
 *@todo fix bug with reading location!
 *
 * @return true on success.
 */
bool CharacterFactory::releaseCharacter(Character *characterReleased)
{
	characterFactory->readyCharacters.push_back(characterReleased);
	std::vector<Character *>::iterator umIter;
	for (umIter=characterFactory->usedCharacters.begin(); umIter < usedCharacters.end(); umIter++ )
	{
		if ((*umIter) == characterReleased)
		{
			usedCharacters.erase(umIter);
		}
	}


	//printf("CharacterFactory::releaseCharacter(Character*): I DO NOTHING!\n");
	return true;
}
