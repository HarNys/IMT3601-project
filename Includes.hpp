#ifndef __IMT3601__INCLUDES__HEADER__GUARD__
#define __IMT3601__INCLUDES__HEADER__GUARD__

///////////// OS SPECIFIC //////////////
#ifdef _WIN32
// we are on windows

#elif defined __linux__
//we are on linux
#include <SFML/Window.hpp>

#elif defined __APPLE__&__MACH__
// we are on mac

#endif // os specific

//////////// ISO LIBRARIES /////////////
#include <stdio.h>

///////// LOCAL PROJECT FILES //////////
#include "classes/World.hpp"
#include "classes/Character.hpp"
#include "classes/Mine.hpp"

#endif //__IMT3601__INCLUDES__HEADER__GUARD__
