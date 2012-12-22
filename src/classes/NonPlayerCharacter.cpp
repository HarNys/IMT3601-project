/*
 * NonPlayerCharacter.cpp
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

NonPlayerCharacter::NonPlayerCharacter()
{
	startNode = NULL;
	goalNode = NULL;
}

/**
 * @brief finds shortest path and gives node pointers to player to calculate velocity
 * @param map the map in question, not really needed.
 * @param thisCharacter Character that is to be moved.
 * @todo give a list of coordinates to visit, so search can be done more rarely.
 */
void NonPlayerCharacter::aStar(Tile*** const map, Character* thisCharacter)
{
	Tile * thisTile = NULL;
	Node * visitNode;
	Node * tempNode;
	bool stackFlag = false;
	int area;

	Node * stackNode = NULL;


	World * check =  World::getWorld();
	area = check->getArea();

	for (int yCount = 0; yCount < area; yCount++)
	{
		for (int xCount =0; xCount < area; xCount++)
		{
			thisTile = map[xCount] [yCount];
			//should not be needed if the character could know position as well.
			if (thisCharacter == thisTile->getHasCharacter()) {
				startNode = new Node(xCount, yCount, 0, 0, 0, NULL);
				startNode->unVisit();
			}

			if (thisTile->getIsGoal()) {
				goalNode = new Node(xCount, yCount, 0, xCount, yCount, NULL);
				goalNode->unVisit();
			}
		}
	}

	//until a complete stack has flagged
	while (!stackFlag && goalNode)
	{
		visitNode = startNode->findCheapestUnusedRecursively();

		if (visitNode)
		{
		visitNode->setVisit();


			//when the goal has been reached, meaning they can create a stack
			// @todo add actual stack instead of two node pointers
			if( visitNode->getXPos() == goalNode->getXPos()
				&& visitNode->getYPos() == goalNode->getYPos())
			{
				stackNode = visitNode;

				thisCharacter->newStack(stackNode->getXPos(), stackNode->getYPos());
				if (startNode != stackNode)
				{
					while (startNode != stackNode)
					{
						stackNode = stackNode->getParent();
						thisCharacter->addStack(stackNode->getXPos(), stackNode->getYPos());
					}

					stackFlag = true;

					tempNode = stackNode->getParent();

				}

				else
				{
					//means no move is necessary
					tempNode = startNode;
				}

			}

				//when goal is not reached
			else
			{
				//adds new nodes to the frontier
				visitNode->setUpChild(addFrontier(visitNode->getXPos(), visitNode->getYPos(), 0, -1, visitNode, thisCharacter));
				visitNode->setRightChild(addFrontier(visitNode->getXPos(), visitNode->getYPos(), 1, 0, visitNode, thisCharacter));
				visitNode->setDownChild(addFrontier(visitNode->getXPos(), visitNode->getYPos(), 0, 1, visitNode, thisCharacter));
				visitNode->setLeftChild(addFrontier(visitNode->getXPos(), visitNode->getYPos(), -1, 0, visitNode, thisCharacter));
			}
		}
		else
		{
			stackFlag = true;
		}
	}


	//call tree destructor
	//pthread lol
	//	loldestroyeverything
	if (startNode)
	{
		delete startNode;
	}
	if (goalNode)
	{
		delete goalNode;
	}

}


Node *NonPlayerCharacter::addFrontier(int xCoord, int yCoord, int xDir, int yDir, Node *nodeParent, Character* movingChar)
{
	if (startNode)
	{
		if (!startNode->checkTreeRecursivelyForNode(xCoord+xDir, yCoord+yDir)){
			//checking for wall in the direction
			World* world = world->getWorld();
			Tile ***map = world->getMap();
			Tile* thisTile = map [xCoord+xDir] [yCoord+yDir];

			if  (!thisTile->getIsWall()){ //checks if tile has a wall
				if (!thisTile->getHasCharacter())
				{
					Node* tempNode;
					tempNode = new Node(xCoord+xDir, yCoord+yDir, nodeParent->getLevel()+1, goalNode->getXPos(), goalNode->getYPos(), nodeParent);
					return tempNode;
				}
				else {
					int nodeCost;
					Character* onTileCharacter;
					onTileCharacter = thisTile->getHasCharacter();
					nodeCost = 5;
					nodeCost += movingChar->getPoints();
					nodeCost -= movingChar->getHealth();
					nodeCost -= onTileCharacter->getPoints();


					Node* tempNode;
					tempNode = new Node(xCoord+xDir, yCoord+yDir, nodeParent->getLevel()+nodeCost, goalNode->getXPos(), goalNode->getYPos(), nodeParent);
					return tempNode;

				}
			}

		}
	}
	return NULL;
}
