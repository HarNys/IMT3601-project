#include "../Includes.hpp"

World *World::world = NULL;

/**
 * @brief Loads a hardcoded map, to create  map variable
 * *
 * @todo solve the problem with write errors that show up when loading occurs
 * @todo separate constructor and map init/loading
 */
World::World()
{
	mineFactory = mineFactory->getMineFactory();
	///@note loading the file that has the map
	std::ifstream file;
//	file.open ("map/mega.txt");
	file.open ("map/maptwo.txt");
	//sf::Image tile;
	///@note creates a temp file for the chars
	area = 0;
	while (file.get()!='\n'){
		area++;
	}
	file.seekg(0);
	///@note creates the map as tiles
	/// Initializes the tile images
	map = new Tile**[area];
	Tile *tempTile = new Tile();
	tempTile->initImage();
	///@note the y value of the map
	for (int i = 0; i<area; i++)
	{
		///@note creates tile pointer for each row
		map[i] = new Tile*[area];

		///@note the x value of the map
		for (int j = 0; j<area; j++)
		{
			///@note makes sure the file is not overextended, this is meant to be redundant
			if(!file.eof())
			{
				map[i][j] = new Tile(*tempTile);
				map[i][j]->initTile(file.get());
				if (map[i][j]->initSprite(i, j))
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
};

/**
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
 * this may be BS.
 */
bool World::placeMine()
{
	mineFactory->getMine();
	printf("Character::characterInput(sf::Event e): Mine placed\n");
	return true;
};

/**
 * runs through all active tiles(tiles within 'area'), and updates them
 * according to the characters and mines on them.
 *
 * @note we may want to reset "this{Tile, Mine, Character}" after each yCount
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
	Tile *nextTile = NULL;
	Mine *thisMine = NULL;
	Mine *tempPlaceMine = NULL;
	Character *thisCharacter = NULL;
	static sf::Clock fpsUpdateTimer;
	int thisCharacterDirectionX = 0;
	int thisCharacterDirectionY = 0;
	float ticksTime = 10;

	// start of operations
//	printf("World::update(): FPS: %d\n",fpsUpdateTimer.getElapsedTime().asMilliseconds());
	if ((fpsUpdateTimer.getElapsedTime().asMicroseconds()) > ticksTime)
	{
		printf("World::update(): FPS: %d\n",fpsUpdateTimer.getElapsedTime().asMilliseconds());
		fpsUpdateTimer.restart();
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
	//					printf("World::update(): thisCharacter exists on Tile: %dX, %dY\n", xCount, yCount);
						if (thisCharacter->getMinePlaced())
						{
							tempPlaceMine = mineFactory->getMine();
							if (tempPlaceMine)
							{
								thisTile->setMine(tempPlaceMine);
								thisTile->setFloor(true);
							}
							thisCharacter->setMinePlaced(false);
						}
						thisCharacterDirectionX = (int) thisCharacter->getCharacterDirectionX();
						thisCharacterDirectionY = (int) thisCharacter->getCharacterDirectionY();
						if (thisCharacterDirectionX != 0) ///< this check may not be necessary
						{ // check and move if possible X++
							if ((xCount + thisCharacterDirectionX) < area)
							{
								nextTile = map[xCount + thisCharacterDirectionX][yCount];
								if (!nextTile->getIsWall())
								{
									if (!nextTile->getHasCharacter())
									{
										thisTile->setCharacter(NULL);
										nextTile->setCharacter(thisCharacter);
										if (nextTile->getHasMine())
										{
											nextTile->getHasMine()->update(thisCharacter);
										}
									}
								}
								else
								{
									printf("World::update(): can't move, there is a wall in "
										"direction %dX\n",thisCharacterDirectionX);
								}
							}
						}
						if (thisCharacterDirectionY != 0) ///< this check may also not be necessary
						{ // check and move if possible Y++
							if ((yCount + thisCharacterDirectionY) < area)
							{
								nextTile = map[xCount][yCount + thisCharacterDirectionY];
								if (!nextTile->getIsWall())
								{
									if (!nextTile->getHasCharacter())
									{
										thisTile->setCharacter(NULL);
										nextTile->setCharacter(thisCharacter);
										if (nextTile->getHasMine())
										{
											nextTile->getHasMine()->update(thisCharacter);
										}
									}
								}
								else
								{
									printf("World::update(): can't move, there is a wall in "
										"direction %dY\n",thisCharacterDirectionY);
								}
							}
						}
						thisCharacter->resetDirection();
					}
				} // end if (!thisTile->getIsWall())
			} // end xCount
		} // end yCount
	}
	return true;
};

/**
 * draws the map to screen.
 *
 * @param [in] window: pointer to the window shit should be placed in
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
//				thisCharacter->draw(window);
			}
		}
	}
};
