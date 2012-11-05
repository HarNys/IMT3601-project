#include "../Includes.hpp"



StackNode::StackNode (int xPosition, int yPosition, StackNode * nextNode)
{
positionX = xPosition;
positionY = yPosition;
next = nextNode;
};
StackNode::StackNode ()
{
positionX = NULL;
positionY = NULL;
next = NULL;
}

StackNode::~StackNode(){
				
};

int StackNode::getXPos(){
	return positionX;
};
int StackNode::getYPos(){
	return positionY;
};

StackNode * StackNode::getNext(){
	return next;
};