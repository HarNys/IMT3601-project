/*
 * Player.cpp
 *
 * Copyright 2012 Peer Andreas Stange <peerandreas@live.com>
 * Copyright 2012 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
 * Copyright 2012 Harry Nystad <harry.ny@live.no>
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

/**
 * movement-functions
 * checks if the key is pressed and then released
 * to reset characterDirectionX/Y
 * @param [in] thisCharacter pointer to character to move.
 *
 * @todo WTF?! Fix this from polling to event queing.
 */

void LocalPlayer::characterInput(Character* thisCharacter)
{

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		thisCharacter->setCharacterDirectionX(-1);
		thisCharacter->updateSprite();

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		thisCharacter->setCharacterDirectionX(1);
		thisCharacter->updateSprite();

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		thisCharacter->setCharacterDirectionY(-1);
		thisCharacter->updateSprite();

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		thisCharacter->setCharacterDirectionY(1);
		thisCharacter->updateSprite();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		thisCharacter->placeMine();
	}

}
