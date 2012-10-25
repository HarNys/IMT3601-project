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
	return true;
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
	int xSpace = 1;
	while (map[xSpace][1]->getIsWall())
	{
		xSpace++;
	}
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

	//
	static bool goalExists;


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
						thisTile->setFloor(1);
					}
					else
					{
						thisTile->setFloor(0);
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

					if (goalExists)
					{
						npcController.aStar(map, thisCharacter);
					}
				}

				if (thisTile->getIsGoal())
				{
					thisTile->setFloor(2);
					goalExists = true;

					if (thisTile->getHasCharacter())
					{
						///<@Todo: give character points
						thisTile->setGoal(false);
						goalExists = false;
					}
				}
			} // end if (!thisTile->getIsWall())
		} // end xCount
	} // end yCount

	if (!goalExists)		//if the is no goal then make one;
	{
		setGoal();
	}

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
/*				thisCharacter->getSprite()->setPosition(((float)(15 * xCount)), ((float)(15 * yCount)));
				thisCharacter->setSprite().setTextureRect(sf::IntRect(0, 51, 15, 15));
//*/
				thisCharacter->updateSprite((float) xCount, (float) yCount);
				window->draw(*thisCharacter->getSprite());
			}
		}
	}
};


void World::setGoal()
{
	Tile* thisTile;
	int x;
	int y;
	srand(time(NULL));
	do				//Do while tile (x,y) is a wall
	{
		do			//DO while tile (x,y) is on the border
		{
			x = (rand()%(area-2))+1;
			y = (rand()%(area-2))+1;
		}while((x == area) || (0 == x) || (y == area) || (0 == y));

		thisTile = map[x][y];

	}while(thisTile->getIsWall());

	thisTile->setGoal(true);
}

Tile ***World::getMap()
{
	return map;
}

int World::getArea(){
	return area;
}


bool World::reset()
{
	Tile *thisTile;
	CharacterFactory* characterFetcher;
	Character* tempCharacter;

	int yCount;
	int xCount;

	for (yCount = 0; yCount < area; yCount++)
	{
		for (xCount = 0; xCount < area; xCount++)
		{
			thisTile = map[xCount][yCount];
			thisTile->reset();
		}

	}

	characterFetcher = characterFetcher->getCharacterFactory();
	tempCharacter = characterFetcher->getCharacter(1);
	placeCharacter(tempCharacter);

	return true;
}
