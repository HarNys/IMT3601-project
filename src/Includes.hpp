/*
 * Includes.hpp
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
#ifndef __IMT3601__INCLUDES__HEADER__GUARD__
#define __IMT3601__INCLUDES__HEADER__GUARD__

///////////// OS SPECIFIC //////////////
#ifdef _WIN32
// we are on windows
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Thread.hpp>

#elif defined __linux__
//we are on linux
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio/Music.hpp>

#elif defined __APPLE__&__MACH__
// we are on mac

#endif // os specific

//////////// ISO LIBRARIES /////////////
#include <stdio.h>
#include <typeinfo>
#include <string.h>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <math.h>
#include <omp.h>


///////// LOCAL PROJECT FILES //////////
#include "classes/Node.hpp"
#include "classes/StackNode.hpp"
#include "classes/Character.hpp" //requires 'Node.hpp' and 'StackNode.hpp'
#include "classes/CharacterFactory.hpp" // requires 'Character.hpp'
#include "classes/Mine.hpp" // requires character
#include "classes/MineFactory.hpp" // requires 'Mine.hpp'
#include "classes/Tile.hpp"
#include "classes/World.hpp"
#include "classes/NonPlayerCharacter.hpp" // requires Node
#include "classes/Player.hpp"
#include "classes/Menu.hpp"


//// Controllers ////
	static LocalPlayer localPlayerController;
	static NonPlayerCharacter npcController;
//*/

#endif //__IMT3601__INCLUDES__HEADER__GUARD__
