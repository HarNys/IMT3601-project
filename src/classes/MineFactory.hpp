/*
 * MineFactory.hpp
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
#ifndef __MINE__FACTORY__HEADER__GUARD__
#define __MINE__FACTORY__HEADER__GUARD__

#include "../Includes.hpp"
/**
 * @brief The MineFactory, creates the grand total of mines for this map setup.
 *
 * @todo should get instance and init in System.
 * @note later we may want to have a constructor with a size parameter.
 * @todo implement lock mechanism
 */
class MineFactory
{
private:
	// constructor
        MineFactory();
        // member variables
        static MineFactory *mineFactory;
	std::vector<Mine *> readyMines;
	std::vector<Mine *> usedMines;
public:
	static MineFactory *getMineFactory();
	Mine *getMine();
	void releaseMine(Mine *releasedMine);
	bool resizeMineFactory(int possibleTotal);
	~MineFactory();
};

#endif // __MINE__FACTORY__HEADER__GUARD__
