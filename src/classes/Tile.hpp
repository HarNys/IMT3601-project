/*
 * Tile.hpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
 * Copyright 2012 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
 * Copyright 2012 Harry Nystad <harry.ny@live.no>
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
#ifndef __TILE__HEADER__GUARD__
#define __TILE__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @par
 * 	The 'World's map arrays contains a set of 'Tile' objects(or
 * 	pointers rather). Each tile currently has a bool for whether or
 * 	not it is a floor or wall tile, a pointer to a 'Mine' object,
 * 	and a pointer to a 'Character' object.
 * @par
 * 	The pointers to 'Mine' and 'Character' will be a NULL pointer.
 */
class Tile
{
private:
	bool isWall; ///< @note isWall is true when 'Tile' is a wall.
	bool visited; ///< @note visited is used for procedural generation'
	bool partOfFrontier;
	bool isGoal;
	Mine *hasMine;
	Character *hasCharacter;
	MineFactory *mineFactory;
	CharacterFactory *characterFactory;
	static sf::Image *wallImg;
	static sf::Image *floorImg;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	int positionX;
	int positionY;

public:
	Tile();
	Tile(char quality);
	void setVisited(bool wall, int xPos, int yPos);
	void setFrontier();
	bool getVisited();
	bool getFrontier();
	bool setWall(bool wall);
	bool setMine(Mine *mine);
	bool setCharacter(Character *character);
	bool setGoal(bool goal);
	bool getIsWall();
	bool getIsGoal();
	bool reset();
	Mine *getHasMine();
	Character *getHasCharacter();
	bool initSprite(int xPos, int yPos);
	void initImage();
	bool initTile(char quality);
	void setPosition(int xPos, int yPos);
	void setFloor(int floorType);
	~Tile();
	sf::Sprite getSprite();

};

#endif // __TILE__HEADER__GUARD__
