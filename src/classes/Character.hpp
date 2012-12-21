/*
 * Character.hpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas@gmail.com>
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
#ifndef __CHARACTER__HEADER__GUARD__
#define __CHARACTER__HEADER__GUARD__

#include "../Includes.hpp"

/**
 * These could probably be made int's.
 * but this is a performance issue.
 */
class Character
{
private:
	//member variables
	bool minePlaced; ///< whether or not we want to place a Mine.
	int characterDirectionX; ///< Changed from float to int
	int characterDirectionY; ///< Changed from float to int
	int characterHealth;	///< How much health the player has left
	static sf::Image *characterImage;
	enum type{mine,rifle};
	int controllerType;		///< 0 for localplayer, 1 for NPC, 2 for networkPlayer.
	int characterID;
	int lastUpdate;
	int pointsValue;
	sf::Texture texture;
	sf::Sprite sprite;
	StackNode *startStack;
	StackNode *endStack;
	int aggressivenes;

public:
	Character();
	bool initImage();
	bool initCharacter(int type, int identity,
		pthread_cond_t *senderCV = NULL);
	bool getMinePlaced();
	void setMinePlaced(bool minePlace);
	int getCharacterDirectionX();
	int getCharacterDirectionY();
	bool setCharacterDirectionX(int newXDirection);
	bool setCharacterDirectionY(int newYDirection);
	void draw(sf::RenderWindow* window);
	void useController(Character* thischaracter);
	void resetDirection();
	void characterInput(sf::Event e);
	bool updateCharacterHealth(int health);
	sf::Sprite *getSprite();
	bool updateSprite(float xPosition, float yPosition);
	void setCurrentNode(Node *newCurrentNode);
	void setNextNode(Node *newNextNode);
	bool updateSprite();
	bool placeMine();
	bool setCharacterType(int type);
	bool setID(int ID);
	void newStack(int xPos, int yPos);
	void addStack(int xPos, int yPos);
	int getType();
	bool setLastUpdate(int time);
	int getLastUpdate();
	int updatePoints(int adjustment);
	bool setAggressivenes(int newaggro);
	int getAggressivenes();
	int getHealth();
	int getPoints();
	pthread_cond_t *getSenderCV();
};

#endif //__CHARACTER__HEADER__GUARD__
