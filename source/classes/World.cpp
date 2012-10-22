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

	border = 1;
	currentX = 1;
	currentY = 1;
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
	map[currentX][currentY]->setVisited();
	return true;
};

/**
* generates a random map
*
* @return true on success
* @todo make this shit work
*/
void World::randomGenerate()
{
	std::map<Tile*,sf::vector2i> *frontier;
	std::list<Tile*> visited;
	int direction = 0;
	int startX = 0;
	int startY = 0;

	direction = (rand() % 4);
	frontier = new std::map<Tile*,sf::vector2i>;
	visited = new std::list<Tile*>;
	startX = (rand() % (area-2) + border);
	startY = (rand() % (area-2) + border);
	printf("World::randomGenerate(): startx:%4d, starty:%4d\n", startX, startY);

	recursiveRandomGenerate(&startX, &startY, frontier, visited);
};

/**
 * Make maze-ish map by doing a recursive depth first search. We only check every
 * other Tile, this way we skip the problems of diagonals and so such.
 *
 * @param currentX The x coordinate we are currently on.
 * @param currentY The y coordinate we are currently on.
 * @param directionX The x direction of the Tile we are trying to visit.
 * @param directionY The y direction of the Tile we are trying to visit.
 * @param frontier The current frontier list.
 *
 * @return true on success.
 */
bool World::recursiveRandomGenerate(int *currentX, int *currentY, int directionX, int directionY, std::list<Tile*> *frontier)
{
	/// Should do the calculations before loop.
	while(visited->size() != ((area * area) - 64))
	{
		if(direction == 0)	//Direction equals up
		{
			if(currentY - 2 > 0)	//as long as I'm not at the border
			{
				currentY = currentY - 2;
				for(iterator = frontier->begin(); iterator != frontier->end(); iterator++, list_position++)
				{
					if(list_position == direction)	//when I'm at the corresponding Direction
					{
						tempTile = *temp_list;	//get the current tile

						if(!tempTile->getVisited())	//if it's not visited
						{
							randomGenerateVisit(map[currentX][currentY], currentX, currentY);

							unVisited->remove(temp);
							visited->push_front(map[currentX][currentY]);

							randomGenerateVisit(map[currentX + direction][currentY], currentX, currentY);

							map[currentX][currentY+1]->setVisited();	//change the tile between current and previous tile to a floor
							map[currentX][currentY+1]->setWall(false);
							map[currentX][currentY+1]->initSprite(currentX, currentY+1);
							visited->push_front(map[currentX][currentY+1]);

							if ((currentX - 2) > 0)
							{
								unVisited->push_front(map[currentX - 2][currentY]);	//push the next 4 on
							}
							if ((currentY + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX][currentY + 2]);
							}
							if ((currentX + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX + 2][currentY]);
							}
							if ((currentY - 2) > 0)
							{
								unVisited->push_front(map[currentX][currentY - 2]);
							}

						}
						else
						{
							unVisited->remove(temp);
							currentY = currentY + 2;
						}
						break;
					}
				}

				randomGenerate();
			}
			else
			{
				unVisited->pop_front(); //pops the top since this is the up dircetion (?)
				randomGenerate();
			}
		}
		else if(Direction == 1)	//Direction equals right
		{
			if(currentX + 2 < (area - border))	//as long as I'm not at the border
			{
				currentX = currentX + 2;
				for(temp_list = unVisited->begin(); temp_list != unVisited->end(); temp_list++, list_position++)
				{
					if(list_position == Direction)	//when I'm at the corresponding Direction
					{
						temp = *temp_list;	//get the current tile

						if(!temp->getVisited())	//if it's not visited
						{
							map[currentX][currentY]->setVisited();	//set it to visited and change tile and texture
							map[currentX][currentY]->setWall(false);
							map[currentX][currentY]->initSprite(currentX, currentY);
							unVisited->remove(temp);
							visited->push_front(map[currentX][currentY]);

							map[currentX-1][currentY]->setVisited();	//change the tile between current and previous tile to a floor
							map[currentX-1][currentY]->setWall(false);
							map[currentX-1][currentY]->initSprite(currentX-1, currentY);
							visited->push_front(map[currentX-1][currentY]);

							if ((currentX - 2) > 0)
							{
								unVisited->push_front(map[currentX - 2][currentY]);	//push the next 4 on
							}
							if ((currentY + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX][currentY + 2]);
							}
							if ((currentX + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX + 2][currentY]);
							}
							if ((currentY - 2) > 0)
							{
								unVisited->push_front(map[currentX][currentY - 2]);
							}

						}
						else
						{
							unVisited->remove(temp);
							currentX = currentX + 2;
						}
						break;
					}
				}

				randomGenerate();
			}
			else
			{
				unVisited->pop_front(); //pops the top since this is the up dircetion (?)
				randomGenerate();
			}
		}
		else if(Direction == 2) //Direction equals down
		{
			if(currentY + 2 < area - border)	//as long as I'm not at the border
			{
				currentY = currentY + 2;
				for(temp_list = unVisited->begin(); temp_list != unVisited->end(); temp_list++, list_position++)
				{
					if(list_position == Direction)	//when I'm at the corresponding Direction
					{
						temp = *temp_list;	//get the current tile

						if(!temp->getVisited())	//if it's not visited
						{
							map[currentX][currentY]->setVisited();	//set it to visited and change tile and texture
							map[currentX][currentY]->setWall(false);
							map[currentX][currentY]->initSprite(currentX, currentY);
							unVisited->remove(temp);
							visited->push_front(map[currentX][currentY]);

							map[currentX][currentY-1]->setVisited();	//change the tile between current and previous tile to a floor
							map[currentX][currentY-1]->setWall(false);
							map[currentX][currentY-1]->initSprite(currentX, currentY-1);
							visited->push_front(map[currentX][currentY-1]);

							if ((currentX - 2) > 0)
							{
								unVisited->push_front(map[currentX - 2][currentY]);	//push the next 4 on
							}
							if ((currentY + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX][currentY + 2]);
							}
							if ((currentX + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX + 2][currentY]);
							}
							if ((currentY - 2) > 0)
							{
								unVisited->push_front(map[currentX][currentY - 2]);
							}

						}
						else
						{
							unVisited->remove(temp);
							currentY = currentY - 2;	//go back to previous tile
						}
						break;
					}
				}
				randomGenerate();
			}
			else
			{
				unVisited->pop_front(); //pops the top since this is the up dircetion (?)
				randomGenerate();
			}
		}
		else if(Direction == 3) //Direction equals left
		{
			if(currentX - 2 > 0)	//as long as I'm not at the border
			{
				currentX = currentX - 2;
				for(temp_list = unVisited->begin(); temp_list != unVisited->end(); temp_list++, list_position++)
				{
					if(list_position == Direction)	//when I'm at the corresponding Direction
					{
						temp = *temp_list;	//get the current tile

						if(!temp->getVisited())	//if it's not visited
						{
							map[currentX][currentY]->setVisited();	//set it to visited and change tile and texture
							map[currentX][currentY]->setWall(false);
							map[currentX][currentY]->initSprite(currentX, currentY);
							unVisited->remove(temp);
							visited->push_front(map[currentX][currentY]);

							map[currentX+1][currentY]->setVisited();	//change the tile between current and previous tile to a floor
							map[currentX+1][currentY]->setWall(false);
							map[currentX+1][currentY]->initSprite(currentX+1, currentY);
							visited->push_front(map[currentX+1][currentY]);

							printf("World::randomGenerate(bool): cx(%d), cy(%d)\n"
								,currentX,currentY);
							if (currentX - 2 > 0)
							{
								printf(	"World::randomGenerate(bool): cx-2(%d)",(currentX-2));
							}

							if ((currentX - 2) > 0)
							{
								unVisited->push_front(map[currentX - 2][currentY]);	//push the next 4 on
							}
							if ((currentY + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX][currentY + 2]);
							}
							if ((currentX + 2) < (area - 2))
							{
								unVisited->push_front(map[currentX + 2][currentY]);
							}
							if ((currentY - 2) > 0)
							{
								unVisited->push_front(map[currentX][currentY - 2]);
							}
						}
						else
						{
							unVisited->remove(temp);
							currentX = currentX + 2;
						}
						break;
					}
				}

				randomGenerate();
			}
			else
			{
				unVisited->pop_front(); //pops the top since this is the up direction (?)
				randomGenerate();
			}
		}
	}
};

/**
 * Visit sent Tile, used in the recursiveRandomGenerate method.
 *
 * @param visitTile pointer to the Tile to be visited.
 *
 * @return true on success.
 */
bool randomGenerateVisit(Tile *visitTile, int xPosition, int yPosition)
{
	visitTile->setWall(false);
	visitTile->initSprite(xPosition, yPosition);
};

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
