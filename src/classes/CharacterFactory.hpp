/*
 * CharacterFactory.hpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas@gmail.com>
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
	Character* getCharacter(); ///< Gets one character for when an event is trigerd
	static CharacterFactory *getCharacterFactory(); ///< Singleton that makes sure only one character factory exists
	bool releaseCharacter(Character *characterReleased);
};



#endif // __CHARACTER__FACTORY__HEADER__GUARD__
