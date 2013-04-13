/*
 * World.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thoams.sigurdsen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
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

	StartX = 0;
	StartY = 0;

	border = 0;

	xSpace = 1;
	updatetime = 0;
	window = NULL;
	mainMenu = NULL;
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
				map[yPosition][xPosition]->setPosition(yPosition, xPosition);
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
};

/**
* generates a random map
*
* @return true on success
* @todo make this shit work
*/
void World::randomGenerate(bool start)
{

	int directionX = 0;
	int directionY = 0;


	static int currentX;
	static int currentY;

	static std::list<Tile*> *unVisited;
	static std::list<Tile*> *visited;
	Tile *temp;
	std::list<Tile*>::iterator temp_list;
	int seed = time(NULL);
	srand(seed);
	int Direction;

	Direction = rand() % 4;


	if(start)
	{
		unVisited = new std::list<Tile*>;
		visited = new std::list<Tile*>;
		StartX = rand() % (area-2) + 1;
		StartY = rand() % (area-2) + 1;
		visited->push_front(map[StartX][StartY]);

		if(StartX - 2 <= border)	//if we could be in danger of going outside the border
			StartX = StartX + 2;
		if(StartX + 2 >= area - 1)
			StartX = StartX - 2;
		if(StartY - 2 <= border)
			StartY = StartY + 2;
		if(StartY >= area - 1)
			StartY = StartY - 2;

		currentX = StartX;
		currentY = StartY;
		map[currentX][currentY]->setVisited(false, currentX, currentY);


		if (currentY - 2 > border)
		{
			map[currentX][currentY - 2]->setFrontier(); //setFrontier sets a variabel to true if it's part of the Frontier
			unVisited->push_front(map[currentX][currentY - 2]);
	//		printf("Currentx: %2d CurrentY: %2d\n", currentX, currentY - 2);
		}
		if (currentX + 2 < area - 1)
		{
			map[currentX + 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX + 2][currentY]);
	//		printf("Currentx: %2d CurrentY: %2d\n", currentX + 2, currentY);
		}
		if (currentY + 2 < area - 1)
		{
			map[currentX][currentY + 2]->setFrontier();
			unVisited->push_front(map[currentX][currentY + 2]);
	//		printf("Currentx: %2d CurrentY: %2d\n", currentX, currentY + 2);
		}
		if (currentX - 2 > border)
		{
			map[currentX - 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX - 2][currentY]);
	//		printf("Currentx: %2d CurrentY: %2d\n", currentX - 2, currentY);
		}
	}
	int count = 0;
	while(!unVisited->empty())
	{
		count++;


	//	printf("1 Unvisited size: %2lud\n", unVisited->size());


		Direction = rand() % 4;
		if(Direction == 0)	//if direction equals up
		{
			directionX = 0;
			directionY = (-2);
		}
		if(Direction == 1)	//if direction equals right
		{
			directionX = (+2);
			directionY = 0;
		}
		if(Direction == 2)	//if direction equals down
		{
			directionX = 0;
			directionY = (+2);
		}
		if(Direction == 3)	//if direction equals left
		{
			directionX = (-2);
			directionY = 0;
		}


	//		printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
	//		"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
	//		"World::randomGenerate(bool): frontier size: %4lu\n\n",
	//		currentX, currentY, directionX, directionY, unVisited->size());

				if(((currentX + directionX) < (area - 1)) &&  ((currentX + directionX) > border) &&
					((currentY + directionY) < (area - 1)) && ((currentY + directionY) > border))
				{
					currentX += directionX;
					currentY += directionY;

					for(temp_list = unVisited->begin(); temp_list != unVisited->end(); temp_list++)
					{
						temp = *temp_list;

						if(temp == map[currentX][currentY])
						{
							map[currentX][currentY]->setVisited(false, currentX, currentY); // set it to visited and change tile and texture
							visited->splice(visited->begin(), *unVisited, temp_list);


							if(((currentX - (directionX/2)) < area - 1) && ((currentX - (directionX/2)) > border) &&
								((currentY - (directionY/2)) < area - 1) && ((currentY - (directionY/2)) > border))
							{
								map[currentX - (directionX/2)][currentY - (directionY/2)]->setVisited(false, currentX - (directionX/2), currentY - (directionY/2));
								visited->push_front(map[currentX - (directionX/2)][currentY - (directionY/2)]);
							}
		//					printf("Visited size: %2lud Unvisited size: %2lud", visited->size(), unVisited->size());
							// push the next 4 on
							if (currentX - 2 > border)
							{
								if (map[currentX - 2][currentY])
								{
									if (!map[currentX - 2][currentY]->getVisited() && !map[currentX - 2][currentY]->getFrontier())	//returns true if it's visited and if it's part of the Frontier
									{
										map[currentX - 2][currentY]->setFrontier();
										unVisited->push_front(map[currentX - 2][currentY]);
		//								printf("Currentx: %2d CurrentY: %2d\n", currentX - 2, currentY);
									}
								}
							}
							if (currentY + 2 < area - 1)
							{
								if(map[currentX][currentY + 2])
								{
									if (!map[currentX][currentY + 2]->getVisited() && !map[currentX][currentY + 2]->getFrontier())
									{
										map[currentX][currentY + 2]->setFrontier();
										unVisited->push_front(map[currentX][currentY + 2]);
			//							printf("Currentx: %2d CurrentY: %2d\n", currentX, currentY + 2);
									}
								}
							}
							if((currentX + 2) < area - 1)
							{
								if(map[currentX + 2][currentY])
								{
									if (!map[currentX + 2][currentY]->getVisited() && !map[currentX + 2][currentY]->getFrontier())
									{
										map[currentX + 2][currentY]->setFrontier();
										unVisited->push_front(map[currentX + 2][currentY]);
			//							printf("Currentx: %2d CurrentY: %2d\n", currentX + 2, currentY);
									}
								}
							}
							if (currentY - 2 > border)
							{
								if(map[currentX][currentY - 2])
								{
									if (!map[currentX][currentY - 2]->getVisited() && !map[currentX][currentY - 2]->getFrontier())
									{
										map[currentX][currentY - 2]->setFrontier();
										unVisited->push_front(map[currentX][currentY - 2]);
				//						printf("Currentx: %2d CurrentY: %2d\n", currentX, currentY - 2);
									}
								}
							}

		//					printf("2 Unvisited size: %2lud\n", unVisited->size());
		//					printf("World::randomGenerate(bool): currX, currY: %2d, %2d\n"
		//					"World::randomGenerate(bool): dirX, dirY: %2d, %2d\n"
		//					"World::randomGenerate(bool): frontier size: %4lu\n",
		//					currentX, currentY, directionX, directionY, unVisited->size());

							if(count % 5 == 0)	//this adds a random tile every 5 step so we create an imperfect maze
							{
								if((map[currentX + 1][currentY] != NULL) &&	(map[currentX + 1][currentY]->getVisited() == false) &&
									(currentX + 1 < area -1))
								{
									map[currentX + 1][currentY]->setVisited(false, currentX + 1, currentY);
								}
								else if((map[currentX - 1][currentY] != NULL) && (map[currentX - 1][currentY]->getVisited() == false) &&
									(currentX - 1 > border))
								{
									map[currentX - 1][currentY]->setVisited(false, currentX - 1, currentY);
								}
								else if((map[currentX][currentY + 1] != NULL) && (map[currentX][currentY + 1]->getVisited() == false) &&
									(currentY + 1 < area -1))
								{
									map[currentX][currentY + 1]->setVisited(false, currentX, currentY + 1);
								}
								else if((map[currentX][currentY - 1] != NULL) && (map[currentX][currentY - 1]->getVisited() == false) &&
									(currentY - 1 > border))
								{
									map[currentX][currentY - 1]->setVisited(false, currentX, currentY - 1);
								}
							}
						break;
						}

					}

			}
			else
			{
		//		printf("!!  unVisited->remove\n");
			}

		if(unVisited->empty())
		{
		//	printf("!!  unVisited->empty()\n");
		}
		else
		{
		//	printf("3 Unvisited size: %2lud\n", unVisited->size());
		}
	}
//	printf("!!  finished !!\n");
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
						if (!nextTile->getHasCharacter()->updateCharacterHealth(-5))
						{
							Character * tempcharacter;
							tempcharacter = nextTile->getHasCharacter();
							nextTile->setCharacter(NULL);
							placeCharacter(tempcharacter);
						}
						whatIsThere = (char *) "there is a Character, stab!";
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


	//#pragma omp critical

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
	updatetime++;
	//
	static bool goalExists;
	static sf::Clock timer;

	int curentTime = timer.getElapsedTime().asMilliseconds();
	//printf("timer is: %d \r ",curentTime);
	curentTime = timer.getElapsedTime().asMilliseconds();

	if(curentTime > 100)
	{
		timer.restart();
		curentTime = timer.getElapsedTime().asSeconds();


		// start of operations

		//#pragma omp for schedule(dynamic)
//		#pragma omp parallel for
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

					if (thisTile->getIsGoal())
					{
						thisTile->setFloor(2);
						goalExists = true;

						if (thisTile->getHasCharacter())
						{
							///<@todo give character points
							thisTile->getHasCharacter()->updatePoints(2);
							thisTile->setGoal(false);
							goalExists = false;
							printf("World::Update(): Character hit flag\n");

						}
					}

					#pragma omp critical(characterMovement)
					{
						if ((thisCharacter = thisTile->getHasCharacter()))
						{

							if(thisCharacter->getLastUpdate() != updatetime)
							{

								thisCharacter->useController(thisCharacter, window);
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
							if (goalExists)
							{
								if (thisCharacter->getIsNpc() && ((thisCharacter->getLastAiUpdate() <= updatetime-5) || !thisCharacter->isStack()))
								{

									//#pragma omp critical(astar)
									//{
										npcController.aStar(map, thisCharacter);
									//}
										thisCharacter->setLastAiUpdate(updatetime);
								}
							}
							thisCharacter->setLastUpdate(updatetime);
						}
					}
				} // end if (!thisTile->getIsWall())
			} // end xCount
		//	int th_id = omp_get_thread_num();
		//	printf ("World::update: numTh: %d, thId: %d\r",
		//		omp_get_num_threads(), th_id);
		} // end yCount
		if (!goalExists)		//if the is no goal then make one;
		{
			setGoal();
		}
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
			thisTile = map[yCount][xCount];
			thisCharacter = thisTile->getHasCharacter();

			// draw the Tile
			window->draw(thisTile->getSprite());
			if (thisCharacter)
			{
//				printf("World::draw(sf::RenderWindow*): should draw a character at this very moment\n");
/*				thisCharacter->getSprite()->setPosition(((float)(15 * xCount)), ((float)(15 * yCount)));
				thisCharacter->setSprite().setTextureRect(sf::IntRect(0, 51, 15, 15));
//*/
				thisCharacter->updateSprite((float) yCount, (float) xCount);
				window->draw(*thisCharacter->getSprite());
			}
		}
	}
};

bool World::placeCharacter(Character *character)
{
	printf("World::placeCharacter(Character *character): Start \n");
	static int small=1;
	static int big=area-2;
	static int rotator=0;
	int increment = 1;
	bool doneflag = false;

	//if (!small && !big && !rotator){
	//small = 1;
	//big = area-2;
	//rotator = 0;
	//}

	while (true)
	{
		if (rotator == 0)
		{
			rotator++;
			if ((map[small][small]->getIsWall() == false)
			&& (map[small][small]->getHasCharacter() == NULL))
			{
				map[small][small]->setCharacter(character);
				character->getSprite()->setPosition(15 * small, 15 * small);
				printf("World::placeCharacter(Character *character): End \n");
				return true;
			}

		}
		if (rotator == 1)
		{
			rotator++;
			if ((map[big][small]->getIsWall() == false)
			&& (map[big][small]->getHasCharacter() == NULL))
			{
				map[big][small]->setCharacter(character);
				character->getSprite()->setPosition(15 * big, 15 * small);
				printf("World::placeCharacter(Character *character): End \n");
				return true;
			}

		}
		if (rotator == 2)
		{
			rotator++;
			if ((map[big][big]->getIsWall() == false)
			&& (map[big][big]->getHasCharacter() == NULL))
			{
				map[big][big]->setCharacter(character);
				character->getSprite()->setPosition(15 * big, 15 * big);
				printf("World::placeCharacter(Character *character): End \n");
				return true;
			}

		}
		if (rotator == 3)
		{
			rotator=0;
			small++;
			big--;
			if ((map[small][big]->getIsWall() == false)
			&& (map[small][big]->getHasCharacter() == NULL))
			{
				map[small][big]->setCharacter(character);
				character->getSprite()->setPosition(15 * small, 15 * big);
				printf("World::placeCharacter(Character *character): End \n");
				return true;
			}

		}


		if (small >= big && doneflag==false)
		{
			small = 1;
			big = area-2;
			doneflag = true;
		}

	}


	return false;
};

/**
*
*	Finds one random tile on the map that is not a wall or a character, and
*	sets that as goal
*
*/
void World::setGoal()
{
	Tile* thisTile;
	int xCoordinate;
	int yCoordinate;
	srand(time(NULL));
	do		//Do while tile (x,y) is a wall or character
	{
		do	//Do while tile (x,y) is on the border
		{
			xCoordinate = (rand()%(area-2))+1;
			yCoordinate = (rand()%(area-2))+1;
		}while((xCoordinate == area) || (0 == xCoordinate) || (yCoordinate == area) || (0 == yCoordinate));

		thisTile = map[xCoordinate][yCoordinate];

	}while(thisTile->getIsWall() || thisTile->getHasCharacter());

	thisTile->setGoal(true);
}

Tile ***World::getMap()
{
	return map;
}

int World::getArea(){
	return area;
}

/**
*	moves through all tiles and emptyes them
*
*/
bool World::reset()
{
	Tile *thisTile;
	CharacterFactory* characterFetcher;
	Character* tempCharacter;

	xSpace = 1;

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
	tempCharacter = characterFetcher->getCharacter();
	placeCharacter(tempCharacter);

	return true;
}

/**
 * sets the sf::RenderWindow for event polling.
 */
bool World::setWindow(sf::RenderWindow *renderWindow)
{
	window = renderWindow;
	mainMenu = new Menu(window);
	return true;
}

/**
 *
 */
bool World::runMenu()
{
	if (window == NULL)
	{
		printf("World::runMenu(): My sf::RenderWindow is NULL, I will therefore die horribly.");
		exit(-1);
	}
	mainMenu->runMenu();
	return true;
}

std::string World::staticMapString()
{
	std::string mapString;
#ifdef _WIN32
	if (area != 0)
	mapString += std::to_string((long long)(area));
	else
	mapString += '4';
#else
	mapString = std::to_string(area);
#endif
	mapString += " 1010101010101010";
	
	for (int yPosition = 0; yPosition < area; yPosition++)
	{
		for (int xPosition = 0; xPosition < area; xPosition++)
		{
			if(map[yPosition][xPosition]->getIsWall())
			{
				mapString += '1';
			}
			else
			{
				mapString += '0';
			}
		}
	}
	return mapString;
}

bool World::buildFromString(std::string baseString)
{	
	std::string::size_type currentPosition;
	area = std::stoi(baseString, &currentPosition);
	if (area <= 9)
	{
		currentPosition+=1;
	}
	else
	{
		currentPosition+=2;
	}

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
			
				map[yPosition][xPosition] = new Tile(*tempTile);
				map[yPosition][xPosition]->setPosition(yPosition, xPosition);
				printf ("%c\n", baseString.at(currentPosition));
				if (baseString.at(currentPosition) == '1')
				{
					map[yPosition][xPosition]->initTile('x');
				}
				else
				{
					map[yPosition][xPosition]->initTile(' ');
				}
				map[yPosition][xPosition]->initSprite(yPosition, xPosition);
				currentPosition++;
		}

	}
	return true;
}