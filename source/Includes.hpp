#ifndef __IMT3601__INCLUDES__HEADER__GUARD__
#define __IMT3601__INCLUDES__HEADER__GUARD__

///////////// OS SPECIFIC //////////////
#ifdef _WIN32
// we are on windows
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D.h>

#elif defined __linux__
//we are on linux
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#elif defined __APPLE__&__MACH__
// we are on mac

#endif // os specific

//////////// ISO LIBRARIES /////////////
#include <stdio.h>
#include <typeinfo>
#include <string.h>
#include <vector>
#include <iostream>

//// OpenMP ////
//#pragma omp

///////// LOCAL PROJECT FILES //////////
#include "classes/Mine.hpp"
#include "classes/MineFactory.hpp" // requires 'Mine.hpp'
#include "classes/Character.hpp"
#include "classes/Tile.hpp"
#include "classes/World.hpp"


#endif //__IMT3601__INCLUDES__HEADER__GUARD__
