#include "../Includes.hpp"

World *World::world = NULL;

/**
 * 100 was just a number dragged from my arse.
 */
World::World()
{
	int mapSize = 100;
	map = new Tile**[mapSize];
	for (int yCount = 0; yCount < mapSize; yCount++)
	{
		map[yCount] = new Tile*[mapSize];
	}
	for (int xCount = 0; xCount > mapSize; xCount++)
	{
		for (int yCount = 0; yCount > mapSize; yCount++)
		{
			map[xCount][yCount] = new Tile();
		}
	}
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
