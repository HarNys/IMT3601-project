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
 * Default constructor for the LocalPlayer class.
 * Will complain if ran, you should use the parameterized constructor.
 * Rationale: being explicit is good.
 */
LocalPlayer::LocalPlayer()
{
	if (DEBUG > 0)
	{
		printf("LocalPlayer::LocalPlayer(): WARNING: Are you "
			"sure you wanted to run the default constructor"
			"?\n");
	}
	isClient = false;
	senderCV = NULL;
}

/**
 * Parameterized constructor for the LocalPlayer class
 * @param iAmClient Whether the game instance is multiplayer client
 * 	(true) or not (false).
 */
LocalPlayer::LocalPlayer(bool iAmClient)
{
	isClient = iAmClient;
	senderCV = NULL;
}

/**
 * Setter for the senderCV variable.
 * @param sentSenderCV The Pthread_cond_t used for synchronisation
 * 	between the LocalPlayer and the NetworkClient classes.
 * @return 0 on success.
 */
int LocalPlayer::setSenderCV(pthread_cond_t *sentSenderCV)
{
	senderCV = sentSenderCV;
	return 0;
}

/**
 * Getter for the senderCV variable.
 * @return senderCV, or NULL if not client
 */
pthread_cond_t *LocalPlayer::getSenderCV()
{
	if (senderCV == NULL)
	{
		if (DEBUG > 0)
		{
			printf("LocalPlayer::getSenderCV(): senderCV is"
				" NULL. Have you forgotten to set it?"
				"\n");
		}
	}
	return senderCV;
}

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] thisCharacter pointer to character to move.
void LocalPlayer::characterInput(Character* thisCharacter)
{
//	sf::Event e; // not used.

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		thisCharacter->setCharacterDirectionX(-1);
		thisCharacter->updateSprite();
		if (senderCV)
		{
			pthread_cond_signal(senderCV);
		}
		//if(e.KeyReleased && e.key.code == sf::Keyboard::A)
		//{
		//	thisCharacter->setCharacterDirectionX(0);
		//}

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		thisCharacter->setCharacterDirectionX(1);
		thisCharacter->updateSprite();
		if (senderCV)
		{
			pthread_cond_signal(senderCV);
		}
		//if(e.KeyReleased && e.key.code == sf::Keyboard::D)
		//{
		//	thisCharacter->setCharacterDirectionX(0);
		//}

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		thisCharacter->setCharacterDirectionY(-1);
		thisCharacter->updateSprite();
		if (senderCV)
		{
			pthread_cond_signal(senderCV);
		}
		//if(e.KeyReleased && e.key.code == sf::Keyboard::W)
		//{
		//	thisCharacter->setCharacterDirectionY(0);
		//}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		thisCharacter->setCharacterDirectionY(1);
		thisCharacter->updateSprite();
		if (senderCV)
		{
			pthread_cond_signal(senderCV);
		}
		//if(e.KeyReleased && e.key.code == sf::Keyboard::S)
		//{
		//	thisCharacter->setCharacterDirectionY(0);
		//}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (senderCV)
		{
			pthread_cond_signal(senderCV);
		}
		//if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		//{
		//	thisCharacter->placeMine();
		//}
	}
};
