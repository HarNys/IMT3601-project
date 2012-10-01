
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
};

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
//	printf("Character::initCharacter(): before texture.loadFromImage(sf::Image)\n");
	texture.loadFromImage(*characterImage);
//	printf("Character::initCharacter(): after texture.loadFromImage(sf::Image)\n");
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
 * @param [in] placeMine: the new value of placeMine
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
 * @bug What is the intention of this function?
 * What it does is not even remotely connected to what it's named
 */
void Character::updatePosition()
{
//	std::cout<< "X-position: " << characterPosX << "\n";
//	std::cout<< "Y-position: " << characterPosY << "\n";
};

/**
 * resets Character's direction, is a dirty way o doing it.
 */
void Character::resetDirection()
{
	characterDirectionX = 0;
	characterDirectionY = 0;
};

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @todo document parameter
void Character::characterInput(sf::Event e)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		characterDirectionX = -1.0;
//		sprite.move(-1.0, 0.0);
//		characterPosX--;
//		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 51, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		characterDirectionX = 1.0;
//		sprite.move(1.0, 0.0);
//		characterPosX++;
//		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 17, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		characterDirectionY = -1.0;
//		sprite.move(0.0, -1.0);
//		characterPosY--;
//		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		characterDirectionY = 1.0;
//		sprite.move(0.0, 1.0);
//		characterPosY++;
//		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 34, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::S)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		MineFactory *mineFactory;
		mineFactory = mineFactory->getMineFactory();

		if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		{
/*			World *world = world->getWorld();
			world->placeMine();
//*/
			minePlaced = true;
			std::cout<< "Character::characterInput(sf::Event e): Mine placed\n";
		}
	}

};

/**
 * places a mine... NEEDS WORK!
 *
 * @todo should place a mine in a space other than RAM
 * @todo what is e?
 */
void Character::placeMine(sf::Event e)
{
	 MineFactory *mineFactory;
	 mineFactory = mineFactory->getMineFactory();

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
