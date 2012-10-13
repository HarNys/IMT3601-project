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
 * @param currentTile the Tile the Character we are trying to move is currently on.
 * @param xPosition the x coordinate Character is currently on.
 * @param yPosition the y coordinate Character is currently on.
 *
 * @return true on succesfull movement.
 *
 * @todo Make this work, and use it in World::update()
 */
 bool World::moveCharacter(Character *character, int xPosition, int yPosition)
 {
	int characterDirectionX = 0;
	int characterDirectionY = 0;
	characterDirectionX = (int) character->getCharacterDirectionX();
	characterDirectionY = (int) character->getCharacterDirectionY();
	if ((characterDirectionX + characterDirectionY) != 0)
	{
		if (((xPosition + characterDirectionX) > 0)
			&& ((yPosition + characterDirectionY) > 0))
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
				}
				else
				{
					printf("World::update(): can't move, there is a wall in "
						"direction %dX\n",characterDirectionX);
					return false;
				}
			}
		}
	}
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
	static sf::Clock fpsUpdateTimer;
//	float ticksTime = 300000;

	// start of operations
	printf("World::update(): FPS: %d\r",fpsUpdateTimer.getElapsedTime().asMilliseconds());
//	if ((fpsUpdateTimer.getElapsedTime().asMicroseconds()) > ticksTime)
//	{
//		printf("World::update(): FPS: %d\r",fpsUpdateTimer.getElapsedTime().asMilliseconds());
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
//	}
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
