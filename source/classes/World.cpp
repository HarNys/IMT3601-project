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


	/**
	 * REALLY UGLY - hardcoded level, should be removed in favor of
	 * 	parser when it gets implemented. current map:
	 * 	X = wall
	 * 	  = floor
	 * 	XXXXXXXXXXX
	 * 	X         X
	 * 	X XX   XX X
	 * 	X X     X X
	 * 	X         X
	 * 	X    X    X
	 * 	X         X
	 * 	X X     X X
	 * 	X XX   XX X
	 * 	X         X
	 * 	XXXXXXXXXXX
	 */
	// y=0
	map[0][0]->setWall(true); map[1][0]->setWall(true);
	map[2][0]->setWall(true); map[3][0]->setWall(true);
	map[4][0]->setWall(true); map[5][0]->setWall(true);
	map[6][0]->setWall(true); map[7][0]->setWall(true);
	map[8][0]->setWall(true); map[9][0]->setWall(true);
	map[10][0]->setWall(true);// map[11][00]->setWall(true);
	// y=1
	map[0][1]->setWall(true); map[1][1]->setWall(false);
	map[2][1]->setWall(false); map[3][1]->setWall(false);
	map[4][1]->setWall(false); map[5][1]->setWall(false);
	map[6][1]->setWall(false); map[7][1]->setWall(false);
	map[8][1]->setWall(false); map[9][1]->setWall(false);
	map[10][1]->setWall(true);// map[11][01]->setWall(true);
	// y=2
	map[0][2]->setWall(true); map[1][2]->setWall(false);
	map[2][2]->setWall(true); map[3][2]->setWall(true);
	map[4][2]->setWall(false); map[5][2]->setWall(false);
	map[6][2]->setWall(false); map[7][2]->setWall(true);
	map[8][2]->setWall(true); map[9][2]->setWall(false);
	map[10][2]->setWall(true);// map[11][02]->setWall(true);
	// y=3
	map[0][3]->setWall(true); map[1][3]->setWall(false);
	map[2][3]->setWall(true); map[3][3]->setWall(false);
	map[4][3]->setWall(false); map[5][3]->setWall(false);
	map[6][3]->setWall(false); map[7][3]->setWall(false);
	map[8][3]->setWall(true); map[9][3]->setWall(false);
	map[10][3]->setWall(true);// map[11][03]->setWall(true);
	// y=4
	map[0][4]->setWall(true); map[1][4]->setWall(false);
	map[2][4]->setWall(false); map[3][4]->setWall(false);
	map[4][4]->setWall(false); map[5][4]->setWall(false);
	map[6][4]->setWall(false); map[7][4]->setWall(false);
	map[8][4]->setWall(false); map[9][4]->setWall(false);
	map[10][4]->setWall(true);// map[11][04]->setWall(true);
	// y=5
	map[0][5]->setWall(true); map[1][5]->setWall(false);
	map[2][5]->setWall(false); map[3][5]->setWall(false);
	map[4][5]->setWall(false); map[5][5]->setWall(false);
	map[6][5]->setWall(true); map[7][5]->setWall(false);
	map[8][5]->setWall(false); map[9][5]->setWall(false);
	map[10][5]->setWall(true);// map[11][5]->setWall(true);
	// y=6
	map[0][6]->setWall(true); map[1][6]->setWall(true);
	map[2][6]->setWall(false); map[3][6]->setWall(false);
	map[4][6]->setWall(false); map[5][6]->setWall(false);
	map[6][6]->setWall(false); map[7][6]->setWall(false);
	map[8][6]->setWall(false); map[9][6]->setWall(false);
	map[10][6]->setWall(true);// map[11][06]->setWall(true);
	// y=7
	map[0][7]->setWall(true); map[1][7]->setWall(false);
	map[2][7]->setWall(false); map[3][7]->setWall(false);
	map[4][7]->setWall(false); map[5][7]->setWall(false);
	map[6][7]->setWall(false); map[7][7]->setWall(false);
	map[8][7]->setWall(true); map[9][7]->setWall(false);
	map[10][7]->setWall(true);// map[11][07]->setWall(true);
	// y=8
	map[0][8]->setWall(true); map[1][8]->setWall(false);
	map[2][8]->setWall(true); map[3][8]->setWall(true);
	map[4][8]->setWall(false); map[5][8]->setWall(false);
	map[6][8]->setWall(false); map[7][8]->setWall(true);
	map[8][8]->setWall(true); map[9][8]->setWall(false);
	map[10][8]->setWall(true);// map[11][08]->setWall(true);
	// y=9
	map[0][9]->setWall(true); map[1][9]->setWall(false);
	map[2][9]->setWall(false); map[3][9]->setWall(false);
	map[4][9]->setWall(false); map[5][9]->setWall(false);
	map[6][9]->setWall(false); map[7][9]->setWall(false);
	map[8][9]->setWall(false); map[9][9]->setWall(true);
	map[10][9]->setWall(false);// map[11][09]->setWall(true);
	// y=10
	map[0][10]->setWall(true); map[1][10]->setWall(true);
	map[2][10]->setWall(true); map[3][10]->setWall(true);
	map[4][10]->setWall(true); map[5][10]->setWall(true);
	map[6][10]->setWall(true); map[7][10]->setWall(true);
	map[8][10]->setWall(true); map[9][10]->setWall(true);
	map[10][10]->setWall(true);// map[11][10]->setWall(true);
	// init sprites
	for (int xCount = 0; xCount < 12; xCount++)
	{
		for (int yCount = 0; yCount < 12; yCount++)
		{
			map[xCount][yCount]->initSprite(xCount, yCount);
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

/**
 * places a character in the world
 *
 * @param [in] character: pointer to the character to be placed.
 *
 * @todo make a proper algorithm for this, requires character factory
 */
bool World::placeCharacter(Character *character)
{
	map[1][1]->setCharacter(character);
	return true;
};
