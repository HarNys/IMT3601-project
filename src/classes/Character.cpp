/*
 * Character.cpp
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

sf::Image *Character::characterImage = NULL;

/**
 * Default constructor for the Character class, called by the CharacterFactory.
 */
Character::Character()
{
	minePlaced = false;
	characterDirectionX = 0;
	characterDirectionY = 0;
	characterHealth = 10;
	controllerType = 1;
	startStack = NULL;
	endStack = NULL;
	lastUpdate = 0;
	sprite.setPosition((15 * 1), (15 * 1));
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
	pointsValue = 0;
	aggressivenes = 0;
};

/**
*	@brief Updates characters healt if it taks demages og health is refreshed etc.
*	@param health The amount of healt to add/subtract.
*	@todo when dead give signal to pop up menu or something like that.
*	@return true if alive, false if dead
*/
bool Character::updateCharacterHealth(int health)
{
	characterHealth += health;
	printf("\nCharacter::updateCharacterHealth(int): player %d's health is %d \r",characterID, characterHealth);
	if(characterHealth < 1)
	{
		updatePoints(-1);
		printf("\n\n---player %d is dead %d points---\n\n",characterID, pointsValue);
		updateCharacterHealth(10);		///< resets characters health if dead
		return false;
	}
	return true;
}

/**
 * loads the static image for the characters, should be done only once
 */
bool Character::initImage()
{
	characterImage = new sf::Image;
	if ((*characterImage).loadFromFile("img/player.gif"))
	{
		printf("Character::initImage(): loaded img/playertrans.gif\n");
	}
	else
	{

		printf("Character::initImage(): could not load image "
			"'img/playertrans.png'\n");
		return false;
	}
	sf::Color alpha(151,251,151);		//Alpha color that is not to be drawn
	characterImage->createMaskFromColor(alpha,0);	//Alpha out the alpha color
	return true;
};

/**
 * initializes the character to the values/states we need it in. should be done
 * after all characterFactory->getCharacter()
 * @todo should have parameters, when we get that far
 *
 * @return true on success
 */
bool Character::initCharacter()
{
	texture.loadFromImage(*characterImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

	return true;
};

/**
 * @return minePlaced
 */
bool Character::getMinePlaced()
{
	return minePlaced;
};

/**
 * @param [in] minePlace: the new value of minePlace.
 */
void Character::setMinePlaced(bool minePlace)
{
	minePlaced = minePlace;
};

/**
 * returns the value of this Character's characterDirectionX.
 *
 * @return characterDirectionX
 */
int Character::getCharacterDirectionX()
{
	return characterDirectionX;
};

/**
 *returns the value of this Character's characterDirectionY.
 *
 * @return characterDirectionY
 */
int Character::getCharacterDirectionY()
{
	return characterDirectionY;
};

/**
 * returns the value of this Character's characterDirectionY.
 *
 * @param newYDirection the new y direction.
 *
 * @return true on success.
 */
bool Character::setCharacterDirectionY(int newYDirection)
{
	printf("Character::setCharacterDirectionY(int): newYDir: %d\n",newYDirection);
	characterDirectionY = newYDirection;
	return true;
};

/**
 * returns the value of this Character's characterDirectionX.
 *
 * @param newXDirection the new x direction.
 *
 * @return true on success.
 */
bool Character::setCharacterDirectionX(int newXDirection)
{
	printf("Character::setCharacterDirectionX(int): newXDir: %d\n",newXDirection);
	characterDirectionX = newXDirection;
	return true;
};

/**
 * Draws the Character's sprite.
 *
 * @param window The game screen we are drawing to/on.
 */
void Character::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
};

/**
 * resets Character's direction, is a dirty way of doing it.
 */
void Character::resetDirection()
{
	characterDirectionX = 0;
	characterDirectionY = 0;
};



/**
 * returns the current sprite.
 *
 * @return the current Character's sprite.
 */
sf::Sprite *Character::getSprite()
{
	return &sprite;
};

/**
 * Updates and sets a Characters sprite position.
 *
 * @param xPosition current x coordinate of the Character.
 * @param yPosition current y coordinate of the Character.
 *
 * @return True on success.
 */
bool Character::updateSprite(float xPosition, float yPosition)
{
	sprite.setPosition((15 * xPosition), (15 * yPosition));
	return true;
}


/**
 * Updates and sets a Characters sprite. The formula for arrowdirection
 * calculates for the img/player.png which square to use. A more easily
 * read form of it would be \f$(17(x^{3}+2x^{2}+y^{3}+y^{2}))\f$
 * or \f$(((x+2)*17*(x*x))+((y+1)*17*(y*y)))\f$. x and y is characterDirectionX
 * and characterDirectionY respectively
 * @return True on success.
 */

bool Character::updateSprite()
{
		int arrowDirection = (17 * (pow((float)characterDirectionX, 3) + (2 * pow((float)characterDirectionX, 2))
		+ pow((float)characterDirectionY, 3) + pow((float)characterDirectionY, 2)));
		sprite.setTextureRect(sf::IntRect(0, arrowDirection, 15, 15));
		return true;
}

/**
*	@param 	thischaracter Character pointer to the character worked on
*/
void Character::useController(Character* thischaracter, sf::RenderWindow *window)
{
	enum controller{PlayerControl, AiControl, NetworkControl};

	if (controllerType == PlayerControl)
	{
		if (window == NULL)
		{
			printf("Character::useController(...): My sf::RenderWindow is NULL, I will therefore die horribly.");
			exit(-1);
		}
		else
		{
			localPlayerController.characterInput(thischaracter, window);
		}
	}
	else if(controllerType == AiControl)
	{
		//npcController.movement(thischaracter);
		if (startStack && endStack)
		{
			if (NULL != startStack->getNext()){
			characterDirectionX = (startStack->getNext()->getXPos() - startStack->getXPos());
			characterDirectionY = (startStack->getNext()->getYPos() - startStack->getYPos());
			StackNode *tempStackNode;
			tempStackNode = startStack->getNext();

			if (startStack)
			{
				delete startStack;
			}

			startStack = tempStackNode;
			}
			thischaracter->updateSprite();
		}

		/// @todo the const should be changed to reflect dificulty
		if (!(rand()%4))
		{
			 characterDirectionX =0;
			 characterDirectionY =0;
		/*	if (tempdirection = 0)
			{
				characterDirectionX = 0;
				characterDirectionY = -1;
			}
			if (tempdirection = 1)
			{
				characterDirectionX = 1;
				characterDirectionY = 0;
			}
			if (tempdirection = 2)
			{
				characterDirectionX = 0;
				characterDirectionY = 1;
			}
			if (tempdirection = 3)
			{
				characterDirectionX = -1;
				characterDirectionY = 0;
			}*/
		}
	}
	else if(controllerType == NetworkControl)
	{

	}

}

/**
*	@brief removes an old stack of movement and creates the first node in a new one
*	@param xPos: coordinate in X
*	@param yPos: coordinate in Y
*/

void Character::newStack(int xPos, int yPos)
{
	if (startStack)
	{
		startStack->removeStack();
	}
	startStack = new StackNode (xPos, yPos);
	endStack = new StackNode (xPos, yPos);

}

/**
*	@brief adds new node to the stack
*	@param xPos: coordinate in X
*	@param yPos: coordinate in Y
*/
void Character::addStack(int xPos, int yPos){
	StackNode *tempStackNode;
	tempStackNode = startStack;
	startStack = new StackNode(xPos, yPos, tempStackNode);

}

/**
 * @todo Documentation.
 */
bool Character::placeMine()
{
	minePlaced = true;
	std::cout<< "Character::characterInput(sf::Event e): Mine placed\n";
	return true;
}


/**
*	@brief sets the typ of character this is
*	@param type: the type of controller 0=local, 1=npc, 2=network
*	@return true on succses
*/
bool Character::setCharacterType(int type)
{
	controllerType = type;
	return true;
}

/**
*	@brief Give the character an ID
*	@param ID: the ID he character is geting
*	@return true on succses
*/
bool Character::setID(int ID)
{
	characterID = ID;
	return true;
}

/**
*	@brief returns true if character is NPC
*	@return true of Npc, false if not.
*/
bool Character::getIsNpc(){
	if (1 == controllerType)
	{
		return true;
	}
	return false;
}

bool Character::setLastUpdate(int time)
{
	lastUpdate = time;
	return true;
}
bool Character::setLastAiUpdate(int time)
{
	lastUpdate = time;
	return true;
}

int Character::getLastUpdate()
{
	return lastUpdate;
}
int Character::getLastAiUpdate()
{
	return lastAiUpdate;
}

int Character::updatePoints(int adjustment)
{
	pointsValue += adjustment;
	return pointsValue;
}

bool Character::setAggressivenes(int newaggro)
{
	aggressivenes = newaggro;
	return true;
}

int Character::getAggressivenes()
{
	return aggressivenes;
}

int Character::getHealth()
{
	return characterHealth;
}
int Character::getPoints()
{
	return pointsValue;
}

bool Character::isStack()
{
	if (startStack)
	{
		if (NULL != startStack->getNext())
		{
			return true;
		}
	}
	return false;
}
