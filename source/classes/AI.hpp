#ifndef __NPC__HEADER__GUARD__
#define __NPC__HEADER__GUARD__
#include "../Includes.hpp"


/** this class is going to have the AI

*/
class NonePlayerCharacter
{
private:


protected:
public:
	void aStar(Tile*** const map);
	void movement(Character* tempchar);

};


#endif  //__AI__HEADER__GUARD__
