#include "../Includes.hpp"

void NonePlayerCharacter::aStar(Tile*** const map, Character* thisCharacter)
{
	//Find character
	
	//if path not defined && path > 3 seconds old

	//Find goal
	//while not goal
	//Open for non walls within reach, assign values as well

	//jump to the square and explore neighbors not already in there, if not visited can readjust values
		
	//end while

	//end if

	//find set of visited to goal and determine what the next step is
	
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
			//needs to be expanded upon so that it can find one set character.
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
				//movement(xDirection, yDirection);
			}
				//when goal is not reached
			else
			{	
				
				//checking for wall above
				thisTile = map [visitNode->getXPos()] [visitNode->getYPos()-1];
				if  (!thisTile->getIsWall()){
					visitNode->upChild = new Node(visitNode->getXPos(), visitNode->getYPos()-1, visitNode->getLevel(), goalNode->getXPos(), goalNode->getYPos(), visitNode);
				}

				thisTile = map [visitNode->getXPos()+1] [visitNode->getYPos()];
				if  (!thisTile->getIsWall()){
					visitNode->rightChild = new Node(visitNode->getXPos()+1, visitNode->getYPos(), visitNode->getLevel(), goalNode->getXPos(), goalNode->getYPos(), visitNode);	
				}
				thisTile = map [visitNode->getXPos()] [visitNode->getYPos()+1];
				if  (!thisTile->getIsWall()){
					visitNode->downChild = new Node(visitNode->getXPos(), visitNode->getYPos()+1, visitNode->getLevel(), goalNode->getXPos(), goalNode->getYPos(), visitNode);
				}
				thisTile = map [visitNode->getXPos()-1] [visitNode->getYPos()];
				if  (!thisTile->getIsWall()){
					visitNode->leftChild = new Node(visitNode->getXPos()-1, visitNode->getYPos(), visitNode->getLevel(), goalNode->getXPos(), goalNode->getYPos(), visitNode);
				}
				
			}
		}
	}

}

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] Character pointer to the character that is going to move

void NonePlayerCharacter::movement(Character* thisCharacter)
{	if((-1) == xDirection)
	{
		thisCharacter->updateSprite(xDirection,yDirection);
		thisCharacter->move('X', xDirection);
	}
	
	if(1 == xDirection)
	{
		thisCharacter->updateSprite(xDirection,yDirection);
		thisCharacter->move('X', xDirection);
	}
	
	if((-1) == yDirection)
	{
		thisCharacter->updateSprite(xDirection,yDirection);
		thisCharacter->move('Y', yDirection);	
	}
	
	if(1 == yDirection)
	{
		thisCharacter->updateSprite(xDirection,yDirection);
		thisCharacter->move('Y', yDirection);
		printf("NonePlayerCharacter::movement(Character*):inside move down if statment \n");
	}


};
