#ifndef __QUEUENODE__HEADER__GUARD__
#define __QUEUENODE__HEADER__GUARD__
#include "../Includes.hpp"

/** This class is going to be a stack to character

*/

class StackNode
{
private:
	StackNode * next;
	int positionX;
	int positionY;
protected:
public:
	StackNode (int xPositon, int yPosition, StackNode * nextNode = NULL);
	StackNode ();
	~StackNode();
	void removeStack();
	StackNode* getNext();
	int getXPos();
	int getYPos();

};

#endif //__QUEUENODE__HEADER__GUARD__