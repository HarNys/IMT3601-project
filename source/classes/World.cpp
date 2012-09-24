#include "../Includes.hpp"

World *World::world = NULL;

/**
 * 100 was just a number dragged from my arse.
 */

/**
 * @brief Loads a hardcoded map, to creat  map variable
 * *
 * @todo solve the problem with write errors that show up when loading occurs
 */
World::World()
{
	///@note loading the file that has the map
	std::ifstream file;
	file.open ("img/map.txt");
	//sf::Image tile;
	///@note creates a temp file for the chars
	const int area = 15;
	//char square[area][area];
	///@note creates the map as tiles
	map = new Tile**[area];
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
				map[i][j] = new Tile(file.get());
				map[i][j]->initSprite(i, j);

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
 * @todo make a proper algorithm for this, requires character factory
 */
bool World::placeCharacter(Character *character)
{
	map[1][1]->setCharacter(character);
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
	for (int xCount = 0; xCount < 15; xCount++)
	{
		for (int yCount = 0; yCount < 15; yCount++)
		{
			window->draw(map[xCount][yCount]->getSprite());
		}
	}
};
