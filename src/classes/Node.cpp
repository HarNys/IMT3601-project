/*
 * Node.cpp
 *
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
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
void Node::unVisit()
{
	visited = false;
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

	if (upChild != NULL)
	{
		tempNode = upChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}
		else if (tempNode!=NULL){
				if (tempNode->getPriority() < smallestNode->getPriority())
				{
					smallestNode = tempNode;
				}
		}

	}
	if (rightChild != NULL)
	{
		tempNode = rightChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		else if (tempNode!=NULL){
				if (tempNode->getPriority() < smallestNode->getPriority())
				{
					smallestNode = tempNode;
				}
		}

	}

	if (downChild != NULL)
	{
		tempNode = downChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		else if (tempNode!=NULL){
				if (tempNode->getPriority() < smallestNode->getPriority())
				{
					smallestNode = tempNode;
				}
		}


	}

	if (leftChild != NULL)
	{
		tempNode = leftChild->findCheapestUnusedRecursively();

		if (smallestNode==NULL)
		{
			smallestNode = tempNode;
		}

		else if (tempNode!=NULL){
				if (tempNode->getPriority() < smallestNode->getPriority())
				{
					smallestNode = tempNode;
				}
		}

	}
	if (smallestNode != NULL)
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

bool Node::checkTreeRecursivelyForNode(int xCoordinates, int yCoordinates){
	// returns the node with the lowest value on priority
	if (xValue == xCoordinates && yValue == yCoordinates){
		return true;
	}
	if (upChild){
		if (upChild->checkTreeRecursivelyForNode(xCoordinates, yCoordinates))
		{
			return true;
		}
	}
	if (rightChild){
		if (rightChild->checkTreeRecursivelyForNode(xCoordinates, yCoordinates))
		{
			return true;
		}
	}
	if(downChild){
		if (downChild->checkTreeRecursivelyForNode(xCoordinates, yCoordinates))
		{
			return true;
		}
	}
	if (leftChild){
		if (leftChild->checkTreeRecursivelyForNode(xCoordinates, yCoordinates))
		{
			return true;
		}
	}
	return false;
};

Node::~Node()
{
	if (upChild)
	{
		delete upChild;
	}

	if (rightChild)
	{
		delete rightChild;
	}

	if (downChild)
	{
		delete downChild;
	}

	if (leftChild)
	{
		delete leftChild;
	}

};

Node* Node::getUpChild()
{
	return upChild;
};

Node* Node::getRightChild()
{
	return rightChild;
};

Node* Node::getDownChild()
{
	return downChild;
};

Node* Node::getLeftChild()
{
	return leftChild;
};

bool Node::setUpChild(Node* newChild)
{
	upChild = newChild;
	return true;
};
bool Node::setRightChild(Node* newChild)
{
	rightChild = newChild;
	return true;
};
bool Node::setDownChild(Node* newChild)
{
	downChild = newChild;
	return true;
};
bool Node::setLeftChild(Node* newChild)
{
	leftChild = newChild;
	return true;
};
