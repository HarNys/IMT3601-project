#ifndef __LOCALPLAYER__HEADER__GUARD__
#define __LOCALPLAYER__HEADER__GUARD__
#include "../Includes.hpp"

class LocalPlayer
{
public:
	void characterInput(sf::Event e, Character* thisCharacter);
};

#endif // __LOCALPLAYER__HEADER__GUARD__