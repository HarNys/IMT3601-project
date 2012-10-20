#include "../Includes.hpp"

void NonePlayerCharacter::aStar(Tile*** const map)
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
	Node * startNode;
	Node * goalNode;
	Node * visitNode;
	int currentXPos;
	int currentYPos;
	bool queueFlag = 0;
	int xTemp;
	int yTemp;

	visitNode = new Node();

	for (int yCount = 0; yCount < area; yCount++)
	{
		for (int xCount =0; xCount < area; xCount++)
		{
			thisTile = map[xCount] [yCount];
			//needs to be expanded upon so that it can find one set character.
			//should not be needed if the character could know position as well.
			if ((*thisTile->getHasCharacter())) {
				startNode = new Node(xCount, yCount, NULL, 0);


			}

			if ((*thisTile->getHasGoal())) {
				goalNode = new Node(xCount, yCount, NULL, 0);
			}
		}
	}

	visitNode = startNode;
	//until a complete queue has flagged
	while (!queueFlag)
	{
		visitNode = startNode->findCheapestUnusedRecursively();
		visitNode->visit();
		//when the goal has been reached, meaning they can create a queue
		if( visitNode->getXPos() != goalNode->getXPos() 
			|| visitNode->getYPos() != goalNode->getYPos())
		{






			queueFlag=1;
		}
		//when goal is not reached
		else
		{			
			
			//checking for wall above
			thisTile = *map [visitNode->getXPos()] [visitNode->getYPos()-1];
			if  (!thisTile->getIsWall()){
				visitNode->up = new Node(visitNode->getXPos(), visitNode->getYPos()-1, visitNode, visitNode->getStep());	
			}

			thisTile = *map [visitNode->getXPos()+1] [visitNode->getYPos()];
			if  (!thisTile->getIsWall()){
				visitNode->right = new Node(visitNode->getXPos()+1, visitNode->getYPos(), visitNode, visitNode->getStep());	
			}
			thisTile = *map [visitNode->getXPos()] [visitNode->getYPos()+1];
			if  (!thisTile->getIsWall()){
				visitNode->down = new Node(visitNode->getXPos(), visitNode->getYPos()+1, visitNode, visitNode->getStep());
			}
			thisTile = *map [visitNode->getXPos()-1] [visitNode->getYPos()];
			if  (!thisTile->getIsWall()){
				visitNode->left = new Node(visitNode->getXPos()-1, visitNode->getYPos(), visitNode, visitNode->getStep());
			}
			


		}
	}

}