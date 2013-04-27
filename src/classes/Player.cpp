/*
 * Player.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
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
 */
void LocalPlayer::characterInput(Character* thisCharacter, sf::RenderWindow *window, bool client)
{
//	printf("LocalPlayer::characterInput(...): I am in function.\n");
	sf::Event event;

	while (window->pollEvent(event))
	{
//		printf("LocalPlayer::characterInput(...): I am polling events.\n");
		if(event.type == sf::Event::KeyPressed)
		{
//			printf("LocalPlayer::characterInput(...): I am recognizing keypresses.\n");
			if (event.key.code == sf::Keyboard::A)
			{
//				printf("LocalPlayer::characterInput(...): I am seeing A.\n");
				thisCharacter->setCharacterDirectionX(-1);
				thisCharacter->updateSprite();
			}
			else if (event.key.code == sf::Keyboard::D)
			{
//				printf("LocalPlayer::characterInput(...): I am seeing D.\n");
				thisCharacter->setCharacterDirectionX(1);
				thisCharacter->updateSprite();
			}
			else if(event.key.code == sf::Keyboard::W)
			{
//				printf("LocalPlayer::characterInput(...): I am seeing W.\n");
				thisCharacter->setCharacterDirectionY(-1);
				thisCharacter->updateSprite();
			}
			else if(event.key.code == sf::Keyboard::S)
			{
//				printf("LocalPlayer::characterInput(...): I am seeing S.\n");
				thisCharacter->setCharacterDirectionY(1);
				thisCharacter->updateSprite();
			}
			else if(event.key.code == sf::Keyboard::E)
			{
//				printf("LocalPlayer::characterInput(...): I am seeing E.\n");
				//	thisCharacter->placeMine();
			}
			/** @todo Review this */
			if(event.key.code == sf::Keyboard::P)
			{
				World *world = world->getWorld();
				world->reset();
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				World *world = world->getWorld();
				world->runMenu();
			}
		}
		if(event.type == sf::Event::KeyReleased)
		{
//			printf("LocalPlayer::characterInput(...): I am recognizing keyreleases.\n");
			if (event.key.code == sf::Keyboard::A)
			{
				thisCharacter->setCharacterDirectionX(0);
				thisCharacter->updateSprite();
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				thisCharacter->setCharacterDirectionX(0);
				thisCharacter->updateSprite();
			}
			else if(event.key.code == sf::Keyboard::W)
			{
				thisCharacter->setCharacterDirectionY(0);
				thisCharacter->updateSprite();
			}
			else if(event.key.code == sf::Keyboard::S)
			{
				thisCharacter->setCharacterDirectionY(0);
				thisCharacter->updateSprite();
			}
		}
		/** @todo this should be reviewed and probably replaced */
		if (event.type == sf::Event::Closed)
		{
			World *world = world->getWorld();
			world->~World();

			/// @bug program segfaults in here, commented
			///	out temporarily
			//mineFactory->~MineFactory();

			window->close();
		}

	}
};
