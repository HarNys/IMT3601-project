#ifndef __IMT3601__INCLUDES__HEADER__GUARD__
#define __IMT3601__INCLUDES__HEADER__GUARD__

///////////// OS SPECIFIC //////////////
#ifdef _WIN32
// we are on windows
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#elif defined __linux__
//we are on linux
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#elif defined __APPLE__&__MACH__
// we are on mac

#endif // os specific

//////////// ISO LIBRARIES /////////////
#include <stdio.h>
#include <typeinfo>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

//// OpenMP ////
//#pragma omp

///////// LOCAL PROJECT FILES //////////
#include "classes/Character.hpp"
#include "classes/CharacterFactory.hpp" // requires 'Character.hpp'
#include "classes/Mine.hpp" // requires character
#include "classes/MineFactory.hpp" // requires 'Mine.hpp'
#include "classes/Tile.hpp"
#include "classes/World.hpp"
#include "classes/AI.hpp"
#include "classes/Node.hpp"
#include "classes/Player.hpp"
#include "classes/Menu.hpp"

//// Controllers ////
static LocalPlayer localPlayerController;
static NonePlayerCharacter npcController;

#endif //__IMT3601__INCLUDES__HEADER__GUARD__
