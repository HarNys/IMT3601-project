#include "../Includes.hpp"

/**
*	@brief finds shortest bath and gives node pointers to player to calculate velocity
*	@param the map in question, not really needed. the character that is to be moved
*	@todo, give a list of coordinates to visit, so search can be done more rarely.
*/

void NonPlayerCharacter::aStar(Tile*** const map, Character* thisCharacter)
{
	Tile * thisTile = NULL;
	Node * visitNode;
	Node * tempNode;
	bool queueFlag = false;
	int area;


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

	//until a complete queue has flagged
	while (!queueFlag && goalNode)
	{
		visitNode = startNode->findCheapestUnusedRecursively();

		if (visitNode)
		{
		visitNode->setVisit();


			//when the goal has been reached, meaning they can create a queue
			// @todo add actual queue instead of two node pointers
			if( visitNode->getXPos() == goalNode->getXPos()
				&& visitNode->getYPos() == goalNode->getYPos())
			{
				queueNode = visitNode;

				if (startNode != queueNode)
				{
					while (startNode != queueNode->getParent() )
					{
						queueNode = queueNode->getParent();
					}

					queueFlag = true;

					tempNode = queueNode->getParent();
				}

				else
				{
					tempNode = startNode;
				}
				thisCharacter->setCurrentNode(tempNode);
				thisCharacter->setNextNode(queueNode);
			}

				//when goal is not reached
			else
			{
				//checks whether node has been created there before
				if (!startNode->checkTreeRecursivelyForNode(visitNode->getXPos(), visitNode->getYPos()-1)){
					//checking for wall above
					if ((visitNode->getYPos() - 1) < area)//map [visitNode->getXPos()] [visitNode->getYPos()-1])
					{
						thisTile = map [visitNode->getXPos()] [visitNode->getYPos()-1];
						if  (!thisTile->getIsWall())
						{
							visitNode->upChild = new Node(visitNode->getXPos(), visitNode->getYPos()-1, visitNode->getLevel()+1, goalNode->getXPos(), goalNode->getYPos(), visitNode);
						}
					}
				}
				//checks whether node has been created there before
				if (!startNode->checkTreeRecursivelyForNode(visitNode->getXPos()+1, visitNode->getYPos())){
					//checking for wall right
					if ((visitNode->getXPos() + 1) < area)//map [visitNode->getXPos()+1] [visitNode->getYPos()])
					{
						thisTile = map [visitNode->getXPos()+1] [visitNode->getYPos()];
						if  (!thisTile->getIsWall())
						{
							visitNode->rightChild = new Node(visitNode->getXPos()+1, visitNode->getYPos(), visitNode->getLevel()+1, goalNode->getXPos(), goalNode->getYPos(), visitNode);
						}
					}
				}
				//checks whether node has been created there before
				if (!startNode->checkTreeRecursivelyForNode(visitNode->getXPos(), visitNode->getYPos()+1)){
					//checking for wall below
					if ((visitNode->getYPos() - 1) < area)//map [visitNode->getXPos()] [visitNode->getYPos()+1])
					{
						thisTile = map [visitNode->getXPos()] [visitNode->getYPos()+1];
						if  (!thisTile->getIsWall())
						{
							visitNode->downChild = new Node(visitNode->getXPos(), visitNode->getYPos()+1, visitNode->getLevel()+1, goalNode->getXPos(), goalNode->getYPos(), visitNode);
						}
					}
				}
				//checks whether node has been created there before
				if (!startNode->checkTreeRecursivelyForNode(visitNode->getXPos()-1, visitNode->getYPos())){
					//checking for wall left
					if ((visitNode->getXPos() - 1) < area)//map[visitNode->getXPos()-1][visitNode->getYPos()])
					{
						thisTile = map[visitNode->getXPos()-1][visitNode->getYPos()];
						if  (!thisTile->getIsWall())
						{
							visitNode->leftChild = new Node(visitNode->getXPos()-1, visitNode->getYPos(), visitNode->getLevel()+1, goalNode->getXPos(), goalNode->getYPos(), visitNode);
						}
					}
				}
			}
		}
		else
		{
			queueFlag = true;
		}
	}

}


