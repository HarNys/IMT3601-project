
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
};

/**
*	@brif: Updates characters healt if it taks demages og health is refreshed etc.
*	@parameter: The amount of healt to add/subtract.
*	@todo: when dead give signal to pop up manu or something like that.
*/
void Character::updateCharacterHealt(int health)
{
	characterHealth += health;
	printf("player health is %d \n",characterHealth);
	if(characterHealth < 1)
	{
		printf("\n\n---You are dead---\n\n");
		updateCharacterHealt(10);		///< resets characters healt if dead

	}
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
float Character::getCharacterDirectionX()
{
	return characterDirectionX;
};

/**
 *returns the value of this Character's characterDirectionY.
 *
 * @return characterDirectionY
 */
float Character::getCharacterDirectionY()
{
	return characterDirectionY;
};

/**
 * @todo document this function
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
*	@param [in]	CharacterDirection(x or y dir), The direction the character is moving(+ - dir), top left corner xand y of the sprite
*			and with and hight of the sprite you want do draw
*/
void Character::move(char CharacterDirection, int moveDirection, int drawTopCornerX, int drawTopCornerY, int drawWith, int drawHight)
{
	sprite.setTextureRect(sf::IntRect(drawTopCornerX, drawTopCornerY, drawWith, drawHight));

	if ('X'== CharacterDirection)
	{
		characterDirectionX = moveDirection;
	}
	else
	{
		characterDirectionY = moveDirection;
	}
	

}


void Character::updatePosition(sf::Event e, Character* thischaracter)
{
	enum controller{PlayerControl, AiControl, NetworkControl};

	if (controllerType == PlayerControl)
	{
		localPlayerController.characterInput(e,thischaracter);
	}
	else if(controllerType == AiControl)
	{
		npcController.movement(thischaracter);
	}
	else if(controllerType == NetworkControl)
	{

	}
}