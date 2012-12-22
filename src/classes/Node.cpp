/*
 * Node.cpp
 *
 * Copyright 2012 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
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


/**
* @brief This constructor creates a node
* @param posx contains the x-position
* @param posy contains the y-position
* @param step shows which level of the tree we are on
* @param goalXValue holds the objectives X-value
* @param goalYValue holds the objectives Y-value
* @param par holds a pointer to the current nodes parent node
*/

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
}

/**
 * @todo Document function
 */
int Node::getXPos()
{
	return xValue;
}

/**
 * @todo Document function
 */
int Node::getYPos ()
{
	return yValue;
}

/**
 * @todo Document function
 */
float Node::getPriority()
{
	return priority;
}

/**
 * @todo Document function
 */
int Node::getLevel()
{
	return level;
}

/**
 * @todo Document function
 */
void Node::setVisit()
{
	visited = true;
}

/**
 * @todo Document function
 */
void Node::unVisit()
{
	visited = false;
}

/**
 * @todo Document function
 */
Node* Node::getParent()
{
	return parent;
}

/**
 * @todo Document function
 */
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
}

/**
 * @todo Document function
 */
bool Node::checkVisited()
{
	return visited;
}

/**
 * @todo Document function
 */
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
}

/**
 * @todo Document function
 */
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

}

/**
 * @todo Document function
 */
Node* Node::getUpChild()
{
	return upChild;
}

/**
 * @todo Document function
 */
Node* Node::getRightChild()
{
	return rightChild;
}

/**
 * @todo Document function
 */
Node* Node::getDownChild()
{
	return downChild;
}

/**
 * @todo Document function
 */
Node* Node::getLeftChild()
{
	return leftChild;
}

/**
 * @todo Document function
 */
bool Node::setUpChild(Node* newChild)
{
	upChild = newChild;
	return true;
}

/**
 * @todo Document function
 */
bool Node::setRightChild(Node* newChild)
{
	rightChild = newChild;
	return true;
}

/**
 * @todo Document function
 */
bool Node::setDownChild(Node* newChild)
{
	downChild = newChild;
	return true;
}

/**
 * @todo Document function
 */
bool Node::setLeftChild(Node* newChild)
{
	leftChild = newChild;
	return true;
}
