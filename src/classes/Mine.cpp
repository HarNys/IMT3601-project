/*
 * Mine.cpp
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
 * Implementation of the mine class's functions
 */
#include "../Includes.hpp"

/**
 * Currently does nothing, we may want to make walking on a mine trigger
 * a function, rather than just damage?
 */
Mine::Mine()
{
	visibilityTimer = 0;
}

/**
 * called when a mine is placed, initializes variables as needed.
 * @param [in] timeShown: the ticks the mine is shown after being planted.
 *
 * @return true on success
 *
 * @todo when we get more Mine types; make this work on a type by type basis
 */
bool Mine::initMine(int timeShown)
{
	visibilityTimer = timeShown;
	return true;
}

/**
 * this is run for every mine on the map.
 *
 * @param [in] character: the character pointer on the same tile as the mine.
 *
 * @return true on success
 */
bool Mine::update(Character *character)
{
	if (character)
	{
		if (DEBUG > 1)
		{
			static int count = 0;
			printf("Mine::update(Character*): BANG! someone triggered a mine %d\n",++count);
		}
		character->updateCharacterHealth((-1));
	}
	return true;
}

/**
 * decrements the invisibility timer.
 *
 * @return false if visibilityTimer is 0. else true.
 */
bool Mine::visibilityCountDown()
{
	visibilityTimer--;
	if (visibilityTimer == 0)
	{
		return false;
	}
	return true;
}
