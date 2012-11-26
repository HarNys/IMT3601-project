#ifndef __NPC__HEADER__GUARD__
#define __NPC__HEADER__GUARD__
#include "../Includes.hpp"


/** this class is going to have the AI

*/
class NonPlayerCharacter
{
private:
Node * startNode;
Node * goalNode;

protected:
public:
	void aStar(Tile*** const map, Character* thisCharacter);
	Node *addFrontier(int xCoord,int yCoord,int xDir,int yDir, Node *nodeParent, Character* movingChar);
	
};


#endif  //__AI__HEADER__GUARD__
	