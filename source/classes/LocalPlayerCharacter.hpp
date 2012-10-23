#ifndef __LOCALPLAYER__HEADER__GUARD__
#define __LOCALPLAYER__HEADER__GUARD__

#include "../Includes.hpp"

class LocalPlayerCharacter : public CharacterController
{
public:
	void characterInput(sf::Event e, Character* tempchar);
};

#endif // __LOCALPLAYER__HEADER__GUARD__
