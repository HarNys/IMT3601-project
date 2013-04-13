/*
 * World.hpp
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
#ifndef __WORLD__HEADER__GUARD__
#define __WORLD__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @brief world X is across, world Y is downwards
 *
 * @todo fix clock for timing of ticks
 * @todo fix the comments
 */
class World
{
private:
	int StartX;
	int StartY;
	int border;
	int xSpace;
	// constructor
	World();

	// member variables
	static World *world;
	Tile ***map;
	int area; //size from origin to one side of the map
	MineFactory *mineFactory;
	int updatetime;
	sf::RenderWindow *window;
	Menu *mainMenu;
public:
	static World *getWorld();
	bool initMap(char *mapFile);
	bool placeCharacter(Character *character);
	bool moveCharacter(Character *character, int xPosition, int yPosition);
	bool placeMine(Character *character, Tile *tile);
	bool update();
	void randomGenerate(bool start);
	void draw(sf::RenderWindow *window);
	Tile ***getMap();
	int getArea();
	void setGoal();
	bool reset();
	bool characterUpdate(Character* thisCharacter, Tile *thisTile,  int xCount, int yCount);
	bool setWindow(sf::RenderWindow *renderWindow);
	bool runMenu();
	std::string World::staticMapString();
};

#endif // __WORLD__HEADER__GUARD__
