/*
 * World.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
 * Copyright 2012 Harry Nystad <harry.ny@live.no>
 * Copyright 2012 rjan Rkkum Brandtzg <orokkum@gmail.com>
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
			// Open it from an audio file
	if (!death.openFromFile("music/death_by _Mediapaja2009_at_freesound.ogg"))
	{
		if (DEBUG > 0)
		{
			printf("Menu::Menu(sf::RenderWindow* renderWindow): can't load music");
		}
	}
	else
	{
		death.setVolume(70);
		death.setLoop(false);
	}

	////////////
	difficulty = 1;  //must be between 1 and 14 controls are in place
	primes[0] = 2;
	primes[1] = 3;
	primes[2] = 5;
	primes[3] = 7;
	primes[4] = 11;
	primes[5] = 13;
	primes[6] = 17;
	primes[7] = 19;
	primes[8] = 23;
	primes[9] = 29;
	primes[10] = 31;
	primes[11] = 37;
	primes[12] = 41;
	primes[13] = 43;
	primes[14] = 47;
	////////////


}

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
}

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
				{
					static int count = 0;
					count++;
				}
			}
		}
		file.ignore(1, '\n');
	}
	file.close();

	return true;
}

/**
 * generates a random map
 *
 * @return true on success
 */
void World::randomGenerate(bool start)
{
	int directionX = 0;	//holds the direction to move on the x-axis
	int directionY = 0; //holds the direction to move on the y-axis
	int count = 0;		//holds the number of times we have been throught the loop, used for creating an imperfect maze
	static int currentX;//current position of the x-axis we are on
	static int currentY;//current position of the y-axis we are on
	static std::list<Tile*> *unVisited;	//holds the list of unvisited tiles on the map
	static std::list<Tile*> *visited; //holds the list of visited tiles on the map
	Tile *temp;
	std::list<Tile*>::iterator tileListIterator; //iterator used to iterate throught the unVisited list
	int seed = time(NULL); //seed with time
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
		}
		if (currentX + 2 < area - 1)
		{
			map[currentX + 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX + 2][currentY]);
		}
		if (currentY + 2 < area - 1)
		{
			map[currentX][currentY + 2]->setFrontier();
			unVisited->push_front(map[currentX][currentY + 2]);
		}
		if (currentX - 2 > border)
		{
			map[currentX - 2][currentY]->setFrontier();
			unVisited->push_front(map[currentX - 2][currentY]);
		}
	}

	while(!unVisited->empty())	//as long at there are tiles in the unVisited list
	{
		count++;


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

				if(((currentX + directionX) < (area - 1)) &&  ((currentX + directionX) > border) &&	//as long as we are in the map area
					((currentY + directionY) < (area - 1)) && ((currentY + directionY) > border))
				{
					currentX += directionX;
					currentY += directionY;

					for(tileListIterator = unVisited->begin(); tileListIterator != unVisited->end(); ++tileListIterator)
					{
						temp = *tileListIterator;	//temp points to the tile in the unVisited list at the tileListIterator position

						if(temp == map[currentX][currentY])
						{
							map[currentX][currentY]->setVisited(false, currentX, currentY); // set it to visited and change tile and texture
							visited->splice(visited->begin(), *unVisited, tileListIterator);


							if(((currentX - (directionX/2)) < area - 1) && ((currentX - (directionX/2)) > border) &&
								((currentY - (directionY/2)) < area - 1) && ((currentY - (directionY/2)) > border))
							{
								map[currentX - (directionX/2)][currentY - (directionY/2)]->setVisited(false, currentX - (directionX/2), currentY - (directionY/2));
								visited->push_front(map[currentX - (directionX/2)][currentY - (directionY/2)]);
							}
							// push the next 4 on
							if (currentX - 2 > border)
							{
								if (map[currentX - 2][currentY])
								{
									if (!map[currentX - 2][currentY]->getVisited() && !map[currentX - 2][currentY]->getFrontier())	//returns true if it's visited and if it's part of the Frontier
									{
										map[currentX - 2][currentY]->setFrontier();
										unVisited->push_front(map[currentX - 2][currentY]);
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
									}
								}
							}


							if(count % 5 == 0  || count % 7 == 0 || count % 9 == 0)	//this adds a random tile every 5 step so we create an imperfect maze
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

	}
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

	int characterDirectionX;
	int characterDirectionY;
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
				Tile *nextTile;
				nextTile = map[xPosition + characterDirectionX][yPosition + characterDirectionY];
				if (!nextTile->getIsWall())
				{
					if (!nextTile->getHasCharacter())
					{
						nextTile->setCharacter(character);
						if (nextTile->getHasMine())
						{
							nextTile->getHasMine()->update(character);
							if (!character->updateCharacterHealth(-5))
							{
								nextTile->setCharacter(NULL);
								placeCharacter(*character);
								death.play();

							}
						}
						return true;
					}
					else
					{
						if (!nextTile->getHasCharacter()->updateCharacterHealth(-10))
						{
							Character * tempcharacter;
							tempcharacter = nextTile->getHasCharacter();
							nextTile->setCharacter(NULL);
							placeCharacter(*tempcharacter);
							death.play();
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
	if (DEBUG > 1)
	{
		printf("World::moveCharacter(): can't move: %s at: %d, %d\n",
			whatIsThere,(xPosition + characterDirectionX), (yPosition + characterDirectionY));
	}


	//#pragma omp critical

	return false;
}

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
}

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
	if (DEBUG > 1)
	{
		printf("World::update(): in World::update()\n");
	}
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
	if (DEBUG > 1)
	{
		printf("timer is: %d \r ",curentTime);
	}
//	curentTime = timer.getElapsedTime().asMilliseconds(); // Allready has this value.

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
						if (thisMine->visibilityCountDown() > 0)
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
							thisTile->getHasCharacter()->updatePoints(2);
							thisTile->setGoal(false);
							goalExists = false;
							if (DEBUG > 1)
							{
								printf("World::Update(): Character hit flag\n");
							}
						}
					}

					#pragma omp critical(characterMovement)
					{
						if ((thisCharacter = thisTile->getHasCharacter()))
						{

							if(thisCharacter->getLastUpdate() != updatetime)
							{
							//	scoreboard->setNewElement(thisCharacter->getID(), thisCharacter->getPoints());
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
								if (thisCharacter->getIsNpc())
								{

									if ((thisCharacter->getLastAiUpdate() <= updatetime-(14-difficulty)) || !thisCharacter->isStack())
									{
									//#pragma omp critical(astar)
									//{
										npcController.aStar(map, thisCharacter);
									//}
										thisCharacter->setLastAiUpdate(updatetime);
									}
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
		if (!goalExists) // If there is no goal then make one;
		{
			setGoal();
		}
		//scoreboard->printList();
	}
	return true;
}

/**
 * Draws this World Tile's and Character's.
 *
 * @param [in] window: pointer to the sf::RenderWindow* we draw to.
 */
void World::draw(sf::RenderWindow *window)
{
	if (DEBUG > 2)
	{
		printf("World::draw(sf::RenderWindow*): in World::draw(sf::RenderWindow*)\n");
	}
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
}

/**
 * @param the character to be placed
 * @return true if it succeeds false if not
 * @brief places the character on a square on one of the corners of a spiral of decreasing size, static to place in new spots
 */
bool World::placeCharacter(Character &character)
{
	if (DEBUG > 1)
	{
		printf("World::placeCharacter(Character *character): Start \n");
	}
	static int small=1;
	static int big=area-2;
	static int rotator=0;
	bool doneflag = false;

	while (true)
	{
		if (rotator == 0)
		{
			rotator++;
			if ((map[small][small]->getIsWall() == false)
			&& (map[small][small]->getHasCharacter() == NULL))
			{
				map[small][small]->setCharacter(&character);
				character.getSprite()->setPosition(15 * small, 15 * small);
				if (DEBUG > 1)
				{
					printf("World::placeCharacter(Character *character): End \n");
				}
				return true;
			}

		}
		if (rotator == 1)
		{
			rotator++;
			if ((map[big][small]->getIsWall() == false)
			&& (map[big][small]->getHasCharacter() == NULL))
			{
				map[big][small]->setCharacter(&character);
				character.getSprite()->setPosition(15 * big, 15 * small);
				if (DEBUG > 1)
				{
					printf("World::placeCharacter(Character *character): End \n");
				}
				return true;
			}

		}
		if (rotator == 2)
		{
			rotator++;
			if ((map[big][big]->getIsWall() == false)
			&& (map[big][big]->getHasCharacter() == NULL))
			{
				map[big][big]->setCharacter(&character);
				character.getSprite()->setPosition(15 * big, 15 * big);
				if (DEBUG > 1)
				{
					printf("World::placeCharacter(Character *character): End \n");
				}
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
				map[small][big]->setCharacter(&character);
				character.getSprite()->setPosition(15 * small, 15 * big);
				if (DEBUG > 1)
				{
					printf("World::placeCharacter(Character *character): End \n");
				}
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
}

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

/**
 * @return the map, which is a tile ***
 */
Tile ***World::getMap()
{
	return map;
}

/**
 * @return value of area
 */
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
	CharacterFactory* characterFactory;//characterFetcher;
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
	characterFactory = characterFactory->getCharacterFactory();
	tempCharacter = characterFactory->getCharacter();
	//placeCharacter(tempCharacter);

	return true;
}

/**
 * @return returns the difficulty assigned to the world
 */
bool World::setWindow(sf::RenderWindow *renderWindow)
{
	window = renderWindow;
	mainMenu = new Menu(window);
	return true;
}

/**
 *
 * @brief modifies the difficulty if it is not higher than max or lower than minimum when modified
 */
bool World::addDifficulty(int modifier)
{
	if (difficulty + modifier <1 || difficulty + modifier >14)
	{
		return false;
	}

	difficulty += modifier;

	return true;
}

/**
 * @return the prime that is wanted
 * @param number, what number of prime is wanted
 */
int World::getPrime(int number)
{
	return primes[number];
}

/**
 * @todo What is this doing here?
*	@brief updates everything for a character.
*	@param Character* thisCharacter: pointer to the character this fuction is going to update for.
*	@param Tile *thisTile: the tile the character is standing on.
*	@param xCount: x position in the world.
*	@param yCount: y position in the world.
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
