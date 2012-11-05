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

	border = 0;
}

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
	}
	return world;
}

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
}

/**
 * Initializes environment for random generation, then calls the generator.
 *
 * @todo evaluate: We may want to do a clean up?
 *
 * @return true on success
 * @todo make this shit work
 */
void World::startRandomGenerate(sf::RenderWindow *screen)
{
	std::list<Tile*> *unVisited;
	unVisited = new std::list<Tile*>;
	srand(time(NULL));

//	std::list<Tile*>::iterator tileListIterator;
// previous if (start) check from here.
	int startX = (rand() % (area-2) + 1); // add border late
	int startY = (rand() % (area-2) + 1);

	if (startX % 2 == 0)
	{
		startX++;
	}
	if (startY % 2 == 0)
	{
		startY++;
	}
	startX = 2;
	startY = 2;

	map[startX][startY]->setVisited(false, startX, startY);
	populateFrontier(startX, startY, unVisited);

/*	if(startX - 2 <= border)	//if we could be in danger of going outside the border
		startX = startX + 2;
	if(startX + 2 >= area - 1)
		startX = startX - 2;
	if(startY - 2 <= border)
		startY = startY + 2;
	if(startY >= area - 1)
		startY = startY - 2;
//*/
//	map[currentX][currentY]->setVisited(false, currentX, currentY);
/*
	if (map[currentX][currentY - 2] != NULL)
	{
		unVisited->push_front(map[currentX][currentY - 2]);
	}
	if (map[currentX + 2][currentY] != NULL)
	{
		unVisited->push_front(map[currentX + 2][currentY]);
	}
	if (map[currentX][currentY+2] != NULL)
	{
		unVisited->push_front(map[currentX][currentY + 2]);
	}
	if (map[currentX - 2][currentY] != NULL)
	{
		unVisited->push_front(map[currentX - 2][currentY]);
	}
//*/
	draw(screen);
	screen->display();
	randomGenerate(startX, startY, unVisited, screen);
}

/**
 * Goes through and generates a map from nothing.
 *
 * @return True on success.
 *
 * @todo fix documentation.
 */
bool World::randomGenerate(int currentX, int currentY, 	std::list<Tile*> *frontierList, sf::RenderWindow *screen)
{
	/*int size = visited->size();
	while(size != ((area * area) - 64))//*/
	int direction = rand() % 4;

	int directionX = 0;
	int directionY = 0;
	if(direction == 0) //if direction equals up
	{ /// @todo Make a check if this means going back to a visited tile
		directionY = (-2);
	}
	if(direction == 1)	//if direction equals right
	{
		directionX = (+2);
	}
	if(direction == 2)	//if direction equals down
	{
		directionY = (+2);
	}
	if(direction == 3)	//if direction equals left
	{
		directionX = (-2);
	}
	printf("World::randomGenerate(): currX, currY: %2d, %2d\n"
		"World::randomGenerate(): dirX, dirY:  %2d, %2d\n"
		"World::randomGenerate(): frontier size:   %4lu\n",
		currentX, currentY, directionX, directionY, frontierList->size());
	if (((currentX + directionX) < 0)
		|| ((currentX + directionX) > area))
	{
		printf("World::randomGenerate(): next X out of bounds: %d\n",
			(currentX + directionX));
		return false;
	}
	if (((currentY + directionY) < 0)
		|| ((currentY + directionY) > area))
	{
		printf("World::randomGenerate(): next Y out of bounds: %d\n",
			(currentY + directionY));
		return false;
	}
	randomGenerateVisit(currentX, currentY, directionX, directionY);
	populateFrontier((currentX + directionX), (currentY + directionY), frontierList);
	draw(screen);
	screen->display();
	if (!frontierList->empty())
	{
		Tile *nextTile = frontierList->back();
		sf::Vector2i *nextTilePosition = NULL;
		frontierList->pop_back();
		nextTilePosition = getTilePosition(nextTile);
		randomGenerate(nextTilePosition->x, nextTilePosition->y, frontierList, screen);
	}

/*
//	while(!frontierList->empty())
//	{
		// If I am inside the border.
		if((currentY + directionY > border)
			&& (currentX + directionX > border)
			&& (currentX + directionX < area - 1)
			&& (currentY + directionY < area - 1))
		{
			currentY = currentY + directionY;
			currentX = currentX + directionX;
//				list_position = 0;
			for(temp_list = frontierList->begin(); temp_list != frontierList->end(); temp_list++)
			{
				temp = *temp_list;
				if(temp == map[currentX][currentY] || previouseTile == map[currentX][currentY])
				{
					if(temp->getVisited() == false)
					{ // if it's not visited
						map[currentX][currentY]->setVisited(false, currentX, currentY); // set it to visited and change tile and texture
						visited->splice(visited->begin(), *frontierList, temp_list);

						//change the tile between current and previous tile to a floor
						map[currentX][currentY]->setVisited(false, currentX + (directionX/2), currentY + (directionY/2));
						visited->push_front(map[currentX + (directionX/2)][currentY + (directionY/2)]);

						// push the next 4 on
						if (currentX - 2 > border)
						{
							if (map[currentX - 2][currentY])
							{
								if (!map[currentX - 2][currentY]->getVisited())
								{
									frontierList->push_front(map[currentX - 2][currentY]);
								}
							}
						}
						if (currentY + 2 <= area - 1)
						{
							if(map[currentX][currentY + 2])
							{
								if (!map[currentX][currentY + 2]->getVisited())
								{
									frontierList->push_front(map[currentX][currentY + 2]);
								}
							}
						}
						if((currentX + 2) <= area - 1)
						{
							if(map[currentX + 2][currentY])
							{
								if (!map[currentX + 2][currentY]->getVisited())
								{
									frontierList->push_front(map[currentX + 2][currentY]);
								}
							}
						}
						if (currentY - 2 > border)
						{
							if(map[currentX][currentY - 2])
							{
								if (!map[currentX][currentY - 2]->getVisited())
								{
									frontierList->push_front(map[currentX][currentY - 2]);
								}
							}
						} //*/
/*							printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
							"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
							"World::randomGenerate(bool): frontier size: %4lu\n",
							currentX, currentY, directionX, directionY, frontierList->size());
							//*/
/*					}
					else	//right now this won't trigger since we are only adding unvisited tiles to frontierList
					{
						frontierList->remove(temp); // remove may be deleting the Tile pointed to, CHECK THIS!
					}
					break;
				}
			}
//			randomGenerate();
		}
//	} //*/
	return true; /// @todo correct? check it
}

/**
 * Visits a Tile and the one before it according to recursive random generating
 * map algorithm.
 *
 * @param xCoordinate the x coordinate we are visiting.
 * @param yCoordinate the y coordinate we are visiting.
 * @param hasMovedDirectionX whether we have moved in the x direction.
 * @param hasMovedDirectionY whether we have moved in the y direction.
 *
 * @return True on success
 */
bool World::randomGenerateVisit(int xCoordinate, int yCoordinate, int hasMovedDirectionX, int hasMovedDirectionY)
{
	if (!map[xCoordinate][yCoordinate]->setVisited(false, xCoordinate, yCoordinate))
	{
		printf("World::randomGenerateVisit(int,int): could not visit Tile at (x,y):"
			"%2d,%2d\n", xCoordinate, yCoordinate);
		return false;
	}
	xCoordinate += hasMovedDirectionX;
	yCoordinate += hasMovedDirectionY;
	if (!map[xCoordinate][yCoordinate]->setVisited(false, xCoordinate, yCoordinate))
	{
		printf("World::randomGenerateVisit(int,int): could not visit Tile at (x,y):"
			"%2d,%2d\n", xCoordinate, yCoordinate);
		return false;
	}
	return true;
}

/**
 * From this point add the four visible Tiles. Will error check for size of area
 * and whether it is already in frontier(not done, see todo)
 *
 * @param currentX The x coordinate of the Tile we are working from
 * @param currentY The y coordinate of the Tile we are working from
 * @param frontier The frontier list we are going to fill/populate.
 *
 * @return True on success.
 *
 * @todo Uniqueness if it is needed? make it so it checks for element in frontier,
 * 	else we could just do the error checking of this in the callee.
 */
bool World::populateFrontier(int currentX, int currentY, std::list<Tile*> *frontier)
{
	if ((currentX - 2) > 0)
	{
		frontier->push_front(map[currentX - 2][currentY]);
	}
	if ((currentX + 2) < area)
	{
		frontier->push_front(map[currentX + 2][currentY]);
	}
	if ((currentY - 2) > 0)
	{
		frontier->push_front(map[currentX][currentY - 2]);
	}
	if ((currentY + 2) < area)
	{
		frontier->push_front(map[currentX][currentY + 2]);
	}
	return true;
}

/**
 * This is a barbaric way of solving the problem of lost coordinates,
 * should not be used outside of randomGeneration.
 *
 * On second thought, should not be used at all, maybe?
 * Function is most probably a performance hit.
 *
 * @param sentTile the Tile we are trying to find the coordinates of.
 *
 * @return The coordinates as a vector, NULL on failure.
 */
sf::Vector2i* World::getTilePosition(Tile *sentTile)
{
	sf::Vector2i *results = NULL;
	for (int xVar = 0; xVar < area; xVar++)
	{
		for (int yVar = 0; yVar < area; yVar++)
		{
			if (map[xVar][yVar] == sentTile)
			{
				results = new sf::Vector2i(xVar, yVar);
				return results;
			}
		}
	}
	return NULL;
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
	map[xSpace++][1]->setCharacter(character);
	character->getSprite()->setPosition(15 * xSpace, 15);
	return true;
}

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
}

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
}

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
}

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
}
