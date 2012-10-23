#ifndef __NPC__HEADER__GUARD__
#define __NPC__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * This class is going to have the AI
 */
class NonPlayerCharacter : public CharacterController
{
private:
	Node* queueNode;
	int xDir;
	int yDir;
protected:
public:
	void aStar(Tile*** const map);
	void movement(Character* tempchar);
};

#endif  //__NPC__HEADER__GUARD__
