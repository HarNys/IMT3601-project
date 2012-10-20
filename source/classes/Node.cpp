#include "../Includes.hpp"


Node(int posx, int posy, Node* par, int step; int goalXValue, int goalYValue)
{
	xValue=posx;
	yValue=posy;
	parent = par;
	level = step;
	double xCube=xValue-goalXValue;
	double yCube=yValue-goalYValue;
	estimate = sqrt((pow(xCube, 2)+pow(yCube, 2)));
	priority = estimate + level;
	
	leftChild =NULL;
	rightChild =NULL;
	upChild =NULL;
	downChild =NULL;
	visited = false;
};
	
int Node::getXPos()
{
	return xValue;
};
	
int Node::getYPos ()
{
	return yValue;
};

float Node::getPriority()
{
	return priority;
};

int Node::getLevel()
{
	return level;
};

void Node::visit()
{
	visited = true;
};

Node* Node::getParent()
{
	return parent;
};

Node* Node::findCheapestUnusedRecursively()
{
	// returns the node with the lowest value on priority
	Node * tempNode = NULL;
	Node * smallestNode = NULL

	if (up){
		tempNode = up->findCheapestUnusedRecursively();
	}
	
	if (tempNode->priority < smallestNode->priority)
	{
		smallestNode = tempNode;
	}
	
	if (right){
		tempNode = right->findCheapestUnusedRecursively();
	}
	if (tempNode->priority < smallestNode->priority)
	{
		smallestNode = tempNode;
	}
	
	
	if (down){
		tempNode = down->findCheapestUnusedRecursively();
	}
	if (tempNode->priority < smallestNode->priority)
	{
		smallestNode = tempNode;
	}
	
	
	if (left){
		tempNode = left->findCheapestUnusedRecursively();
	}
	

	if (tempNode->priority < smallestNode->priority)
	{
		smallestNode = tempNode;
	}
	
	return smallestNode;
};
