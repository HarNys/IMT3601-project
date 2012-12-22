/*
 * Player.hpp
 *
 *
 * Copyright 2012 Peer Andreas Stange <peerandreas@live.com>
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
#ifndef __LOCALPLAYER__HEADER__GUARD__
#define __LOCALPLAYER__HEADER__GUARD__
#include "../Includes.hpp"

class LocalPlayer
{
public:
	void characterInput(Character* thisCharacter);
};

#endif // __LOCALPLAYER__HEADER__GUARD__
