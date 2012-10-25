
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
	controllerType = 0;
	sprite.setPosition((15 * 1), (15 * 1));
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

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
	characterDirectionX = newXDirection;
	return true;
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
};

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
*	@param 	sf::Event e keybordevent,
*	@param 	Character* thischaracter Character pointer to the character worked on
*/

void Character::useController(sf::Event e, Character* thischaracter)
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
//*/
