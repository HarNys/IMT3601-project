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
	///@note loading the file that has the map
	std::ifstream file;
//	file.open ("map/mega.txt");
	file.open ("map/map.txt");
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
	return true;
};

/**
 * runs through all active tiles(tiles within 'area'), and updates them
 * according to the characters and mines on them.
 *
 * @note we may want to reset "this{Tile, Mine, Character}" after each yCount
 *
 * @return true on success
 */
bool World::update()
{
	int xCount = 0;
	int yCount = 0;
	/// area is defined in constructor and header
	Tile *thisTile = NULL;
	Mine *thisMine = NULL;
	Character *thisCharacter = NULL;
	for (; xCount < area; xCount++)
	{
		for (; yCount < area; yCount++)
		{
			thisTile = map[xCount][yCount];
			if (!thisTile->getIsWall())
			{
				if (thisMine = thisTile->getHasMine())
				{
					thisMine->visibilityCountDown();
				}
				if (thisCharacter = thisTile->getHasCharacter())
				{
					//thisCharacter->
				}
			}
		} // end yCount
	} // end xCount
	return true;
};

/**
 * draws the map to screen,
 *
 * @param [in] window: pointer to the window shit should be placed in
 *
 *
 */
void World::draw(sf::RenderWindow *window)
{
	for (int xCount = 0; xCount < area; xCount++)
	{
		for (int yCount = 0; yCount < area; yCount++)
		{
			window->draw(map[xCount][yCount]->getSprite());
		}
	}
};
