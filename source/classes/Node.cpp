#include "../Includes.hpp"


Node::Node(int posx, int posy, int step, int goalXValue, int goalYValue, Node* par)
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

void Node::setVisit()
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
	Node * smallestNode = NULL;

	if (upChild)
	{
		tempNode = upChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		if (tempNode->getPriority() < smallestNode->getPriority())
		{
			smallestNode = tempNode;
		}

	}
	if (rightChild)
	{
		tempNode = rightChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		if (tempNode->getPriority() < smallestNode->getPriority())
		{
			smallestNode = tempNode;
		}

	}

	if (downChild)
	{
		tempNode = downChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		if (tempNode->getPriority() < smallestNode->getPriority())
		{
			smallestNode = tempNode;
		}


	}

	if (leftChild)
	{
		tempNode = leftChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		if (tempNode->getPriority() < smallestNode->getPriority())
		{
			smallestNode = tempNode;
		}

	}
	if (smallestNode)
	{
		if (!smallestNode->checkVisited())
		{
			return smallestNode;
		}

	}
	else if (visited)
	{
		return NULL;
	}
	return this;
};

bool Node::checkVisited()
{
	return visited;
};
