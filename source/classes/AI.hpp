#ifndef __NPC__HEADER__GUARD__
#define __NPC__HEADER__GUARD__
#include "../Includes.hpp"


/** this class is going to have the AI

*/
class NonePlayerCharacter
{
private:
Node* queueNode;
int xDir;
int yDir;

protected:
public:
	void aStar(Tile*** const map);
	void movement(Character* thisCharacter);

};


#endif  //__AI__HEADER__GUARD__
	