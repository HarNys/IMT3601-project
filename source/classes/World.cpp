#include "../Includes.hpp"

World *World::world = NULL;

/**
 * 100 was just a number dragged from my arse.
 */
World::World()
{

	std::ifstream file;
	file.open ("img/map.txt");
	sf::Image tile;

	const int area = 15;
	char square[area][area];
	map = new Tile*[area];

	for (int i = 0; i<area; i++)
	{
		map[i] = new Tile[area];
		for (int j = 0; i<area; j++)
		{
			if(!file.eof())
			{
				if (file.peek()=='!')
				{
					i++;
					j=0;
					file.ignore(2, '!');
					file.ignore(2, '\n');
					std::cout << '\n';

				}

				square[i][j] = file.get();
				std::cout << square[i][j];
				//map[i][j] = new Tile(/*square[i][j]*/);

			//	if(square[i][j]==' ')
			//	{
			//	tile.loadFromFile("img/floor.gif");
			//	}
			//	else if (square[i][j]=='x')
			//	{
			//	tile.loadFromFile("img/wall.gif");
			//	}
//			texture.loadFromImage(tile);
//			sprite.setTexture(texture);
//			sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
//			sprite.setColor(sf::Color(255, 255, 255, 200));
//			sprite.setPosition(16*i, 16*j);

			}

		}

	}




	file.close();
/*
	for (int i = 0; i<area; i++)
	{
		for (int j = 0; i<area; j++)
		{
			std::cout<< square[i][j] << "\n";
		}

	}


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
	//*/

/*	// init sprites
	for (int xCount = 0; xCount < 12; xCount++)
	{
		for (int yCount = 0; yCount < 12; yCount++)
		{
			map[xCount][yCount]->initSprite(xCount, yCount);
		}
	}
//*/
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
	map[1][1].setCharacter(character);
	return true;
};
