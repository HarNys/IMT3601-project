/*
 * Player.hpp
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
/**
 * @todo rename this classes files from Player.{c,h}pp to
 * 	LocalPlayer.{c,h}pp
 */
#ifndef __LOCALPLAYER__HEADER__GUARD__
#define __LOCALPLAYER__HEADER__GUARD__
#include "../Includes.hpp"

class LocalPlayer
{
private:
	/**
	 * isClient is checked to see if we need to signal the
	 * NetworkClient to send. It should only ever be true when this
	 * instance of the game is a multiplayer client.
	 *
	 * Defaults to false in default constructor.
	 */
	bool isClient;
	pthread_cond_t *senderCV;
public:
	LocalPlayer();
	LocalPlayer(bool iAmHost);
	int setSenderCV(pthread_cond_t *sentSenderCV);
	pthread_cond_t *getSenderCV();
	void characterInput(Character* thisCharacter);
};

#endif // __LOCALPLAYER__HEADER__GUARD__
