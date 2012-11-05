#include "../Includes.hpp"

World *World::world = NULL;

/**
 * World constructor. Should only do the bare minimum for using, should
 * initialize in another init function
 *
 * @todo solve the problem with write errors that show up when loading occurs
 * @todo separate constructor and map init/loading
 */
World::World()
{
	mineFactory = mineFactory->getMineFactory();
	area = 0;
	map = NULL;

	StartX = 0;
	StartY = 0;

	border = 0;

};

/**
 * The singleton handler, returns a working World object.
 *
 * @return World singleton object.
 *
 * @todo needs locking when multithreading
 */
World *World::getWorld()
{
	if (world == NULL)
	{
		world = new World();
		return world;
	}
	else
	{
		return world;
	}
};

/**
 * Initializes the map using 'mapFile'
 *
 * @param[in] mapFile the relative path to the text file containing the map to
 * 	be loaded.
 * @param[out] windowSize the size of the window we draw to.
 *
 * @return true on success.
 *
 * @bug It seems this function draws or reads x's and y's swapped.
 */
bool World::initMap(char *mapFile)
{
	if (!map[0][0])
	{
		/**
		 * delete map?
		 */
	}
	/// loading the file that has the map
	std::ifstream file;
	file.open(mapFile);
	area = 0;
	while (file.get() != '\n'){
		area++;
	}
	file.seekg(0);
	map = new Tile**[area];
	Tile *tempTile = new Tile();
	tempTile->initImage();
	for (int yPosition = 0; yPosition < area; yPosition++)
	{
		///@note creates tile pointer for each row
		map[yPosition] = new Tile*[area];

		///@note the x value of the map
		for (int xPosition = 0; xPosition < area; xPosition++)
		{
			///@note makes sure the file is not overextended, this is meant to be redundant
			if(!file.eof())
			{
				map[yPosition][xPosition] = new Tile(*tempTile);
				map[yPosition][xPosition]->initTile(file.get());
				if (map[yPosition][xPosition]->initSprite(yPosition, xPosition))
//					, (windowSize.x/area), (windowSize.y/area)))
				{
					static int count = 0;
					count++;
//					printf("World::World(): count: %i\n", count);
				}
			}
		}
		file.ignore(1, '\n');
	}
	file.close();
//	map[currentX][currentY]->setVisited();
	return true;
};

/**
* generates a random map
*
* @return true on success
* @todo make this shit work
*/
void World::randomGenerate(bool start, Tile *previouseTile)
{
	
	int directionX = 0;
	int directionY = 0;

	int previousX;
	int previousY;
	static int currentX;
	static int currentY;

	int list_position = 1;
	static std::list<Tile*> *unVisited;
	static std::list<Tile*> *visited;
	Tile *temp;
	std::list<Tile*>::iterator temp_list;
	int seed = time(NULL);
	srand(seed);
	int Direction;

	Direction = rand() % 4;

	
	if(start)
	{
		unVisited = new std::list<Tile*>;
		visited = new std::list<Tile*>;
		StartX = rand() % (area-2) + 1; //add border late
		StartY = rand() % (area-2) + 1;
		visited->push_front(map[StartX][StartY]);
		
		if(StartX - 2 <= border)	//if we could be in danger of going outside the border
			StartX = StartX + 2;
		if(StartX + 2 >= area - 1)
			StartX = StartX - 2;
		if(StartY - 2 <= border)
			StartY = StartY + 2;
		if(StartY >= area - 1)
			StartY = StartY - 2;

		currentX = StartX;
		currentY = StartY;
		map[currentX][currentY]->setVisited(false, currentX, currentY);

		
		if (map[currentX][currentY - 2] != NULL)
		{
			map[currentX][currentY - 2]->setFrontier();
			unVisited->push_front(map[currentX][currentY - 2]);
		}
		if (map[currentX + 2][currentY] != NULL)
		{
			map[currentX + 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX + 2][currentY]);
		}
		if (map[currentX][currentY+2] != NULL)
		{
			map[currentX][currentY + 2]->setFrontier();
			unVisited->push_front(map[currentX][currentY + 2]);
		}
		if (map[currentX - 2][currentY] != NULL)
		{
			map[currentX - 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX - 2][currentY]);
		}
	}

		directionX = 0;
		directionY = 0;
		if(Direction == 0)	//if direction equals up
		{   //make a check if this means going back to a visited tile
			directionX = 0;
			directionY = (-2);
		}
		if(Direction == 1)	//if direction equals right
		{
			directionX = (+2);
			directionY = 0;
		}
		if(Direction == 2)	//if direction equals down
		{
			directionX = 0;
			directionY = (+2);
		}
		if(Direction == 3)	//if direction equals left
		{
			directionX = (-2);
			directionY = 0;
		}
		printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
			"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
			"World::randomGenerate(bool): frontier size: %4lu\n",
			currentX, currentY, directionX, directionY, unVisited->size());

		while(!unVisited->empty())
		{
			if(currentY + directionY > border && currentX + directionX > border && currentX + directionX < area - 1 && currentY + directionY < area - 1) //as long as I'm not at the y coordinate border
			{
				currentY = currentY + directionY;			
				currentX = currentX + directionX;

				if(!map[currentX][currentY]->getVisited())
				{
					for(temp_list = unVisited->begin(); list_position <= unVisited->size(); temp_list++, list_position++)
					{
						temp = *temp_list;
						if(temp == map[currentX][currentY])
						{
							
							map[currentX][currentY]->setVisited(false, currentX, currentY); // set it to visited and change tile and texture
							visited->splice(visited->begin(), *unVisited, temp_list);

							//change the tile between current and previous tile to a floor
							map[currentX][currentY]->setVisited(false, currentX - (directionX/2), currentY - (directionY/2));
							visited->push_front(map[currentX - (directionX/2)][currentY - (directionY/2)]);

							// push the next 4 on
							if (currentX - 2 > border)
							{
								if (map[currentX - 2][currentY])
								{
									if (!map[currentX - 2][currentY]->getVisited() && !map[currentX - 2][currentY]->getFrontier())
									{
										map[currentX - 2][currentY]->setFrontier();
										unVisited->push_front(map[currentX - 2][currentY]);
									}
								}
							}
							if (currentY + 2 <= area - 1)
							{
								if(map[currentX][currentY + 2])
								{
									if (!map[currentX][currentY + 2]->getVisited() && !map[currentX][currentY + 2]->getFrontier())
									{
										map[currentX][currentY + 2]->setFrontier();
										unVisited->push_front(map[currentX][currentY + 2]);
									}
								}
							}
							if((currentX + 2) <= area - 1)
							{
								if(map[currentX + 2][currentY])
								{
									if (!map[currentX + 2][currentY]->getVisited() && !map[currentX + 2][currentY]->getFrontier())
									{
										map[currentX + 2][currentY]->setFrontier();
										unVisited->push_front(map[currentX + 2][currentY]);
									}
								}
							}
							if (currentY - 2 > border)
							{
								if(map[currentX][currentY - 2])
								{
									if (!map[currentX][currentY - 2]->getVisited() && !map[currentX][currentY - 2]->getFrontier())
									{
										map[currentX][currentY - 2]->setFrontier();
										unVisited->push_front(map[currentX][currentY - 2]);
									}
								}
							}
								printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
								"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
								"World::randomGenerate(bool): frontier size: %4lu\n",
								currentX, currentY, directionX, directionY, unVisited->size());
								
							
							
							//printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
							//	"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
							//	"World::randomGenerate(bool): frontier size: %4lu\n",
							//	currentX, currentY, directionX, directionY, unVisited->size());
							break;
						}
					}
				}
				else
				{
					unVisited->remove(map[currentX][currentY]); // remove may be deleting the Tile pointed to, CHECK THIS!
				}
				randomGenerate();
			}
			else
				break;
		}
}

/**
 * places a character in the world
 *
 * @param [in] character: pointer to the character to be placed.
 *
 * @return true on success
 *
 * @todo make a proper algorithm for this, requires character factory
 */
bool World::placeCharacter(Character *character)
{
	static int xSpace = 1;
	map[StartX][StartY]->setCharacter(character);
	character->getSprite()->setPosition(15 * xSpace, 15);
	return true;
};

/**
 * Moves Character if possible.
 *
 * @param character Character to we are trying to move.
 * @param xPosition the x coordinate Character is currently on.
 * @param yPosition the y coordinate Character is currently on.
 *
 * @return true on succesfull movement.
 */
bool World::moveCharacter(Character *character, int xPosition, int yPosition)
{
	int characterDirectionX = 0;
	int characterDirectionY = 0;
	characterDirectionX = character->getCharacterDirectionX();
	characterDirectionY = character->getCharacterDirectionY();
	char *whatIsThere = NULL;
	if ((characterDirectionX + characterDirectionY) == 0)
	{
		return false;
	}
	else
	{
		if (((xPosition + characterDirectionX) >= 0)
			&& ((yPosition + characterDirectionY) >= 0))
		{
			if (((xPosition + characterDirectionX) < area)
				&& ((yPosition + characterDirectionY) < area))
			{
				Tile *nextTile = NULL;
				nextTile = map[xPosition + characterDirectionX][yPosition + characterDirectionY];
				if (!nextTile->getIsWall())
				{
					if (!nextTile->getHasCharacter())
					{
						nextTile->setCharacter(character);
						if (nextTile->getHasMine())
						{
							nextTile->getHasMine()->update(character);
						}
						return true;
					}
					else
					{
						whatIsThere = (char *) "there is a Character";
					}
				}
				else
				{
					whatIsThere = (char *) "there is a Wall";
				}
			}
			else
			{
				whatIsThere = (char *) "nextTile is out of bounds, bigger.";
			}
		}
		else
		{
			whatIsThere = (char *) "nextTile is out of bounds, smaller.";
		}
	}
	printf("World::moveCharacter(): can't move: %s at: %d, %d\n",
		whatIsThere,(xPosition + characterDirectionX), (yPosition + characterDirectionY));
	return false;
};

/**
 * Puts a Mine on the Tile parameter.
 *
 * @param[in,out] character The character placing the Mine.
 * @param[out] characterPosition the Tile to place the Mine on.
 *
 * @return true on success
 *
 * @todo fix Minefactory and Mine so it is global for class World.
 */
bool World::placeMine(Character *character, Tile *characterPosition)
{
	Mine *tempPlaceMine = mineFactory->getMine();
	if (tempPlaceMine)
	{
		characterPosition->setMine(tempPlaceMine);
		characterPosition->setFloor(true);
	}
	character->setMinePlaced(false);
	return true;
};

/**
 * runs through all active tiles(tiles within 'area'), and updates them
 * according to the characters and mines on them.
 *
 * @note we may want to reset "this{Tile, Mine, Character}" after each yCount (xCount?)
 * @note this function is turning out to be bigger and and more complex than I
 * 	thought. We may want to break it up into more manageable peices.
 *
 * @return true on success
 */
bool World::update()
{
//	printf("World::update(): in World::update()\n");
	// variables to be used
	int xCount = 0;
	int yCount = 0;
	// area is defined in constructor and header
	Tile *thisTile = NULL;
	Mine *thisMine = NULL;
	Character *thisCharacter = NULL;


	// start of operations
	for (yCount = 0; yCount < area; yCount++)
	{
		for (xCount = 0; xCount < area; xCount++)
		{
			thisTile = map[xCount][yCount];
			if (!thisTile->getIsWall())
			{
				if ((thisMine = thisTile->getHasMine()))
				{
					if (!thisMine->visibilityCountDown())
					{
						thisTile->setFloor(true);
					}
					else
					{
						thisTile->setFloor(false);
					}
				}
				if ((thisCharacter = thisTile->getHasCharacter()))
				{
					if (thisCharacter->getMinePlaced())
					{
						placeMine(thisCharacter, thisTile);
					}
					if (moveCharacter(thisCharacter, xCount, yCount))
					{
						thisTile->setCharacter(NULL);
					}
					thisCharacter->resetDirection();
				}
			} // end if (!thisTile->getIsWall())
		} // end xCount
	} // end yCount
	return true;
};

/**
 * Draws this World Tile's and Character's.
 *
 * @param [in] window: pointer to the sf::RenderWindow* we draw to.
 */
void World::draw(sf::RenderWindow *window)
{
//	printf("World::draw(sf::RenderWindow*): in World::draw(sf::RenderWindow*)\n");
	Tile *thisTile = NULL;
	Character *thisCharacter = NULL;
	for (int yCount = 0; yCount < area; yCount++)
	{
		for (int xCount = 0; xCount < area; xCount++)
		{
			thisTile = map[xCount][yCount];
			thisCharacter = thisTile->getHasCharacter();

			// draw the Tile
			window->draw(thisTile->getSprite());
			if (thisCharacter)
			{
//				printf("World::draw(sf::RenderWindow*): should draw a character at this very moment\n");
				thisCharacter->getSprite()->setPosition(((float)(15 * xCount)), ((float)(15 * yCount)));
				window->draw(*thisCharacter->getSprite());
			}
		}
	}
};
