
#include "../Includes.hpp"

sf::Image *Character::characterImage = NULL;

/**
 * Default constructor for the Character class, called by the CharacterFactory.
 *
 * @todo make this set values to the bare minimum required, use an init method
 * to set values as apropriate.
 */
Character::Character()
{
/*	sf::Image image;
	/// @bug this path is not correct in windows for some reason
	if (image.loadFromFile("img/player.png"))
	{
		printf("Character::Character(): loaded img/player.png\n");
	}
	else
	{
		printf("Character::Character(): could not load image "
			"'img/player.png'\n");
		exit(1);
	}
	sf::Color alpha(151,251,151);		//Alpha color that is not to be drawn
	image.createMaskFromColor(alpha,0);	//Alpha out the alpha color
//*/	//createMaskFromColor

/*	printf("Character::Character(): before texture.loadFromImage(sf::Image)");
	/// @bug segfaults in here it seems
	texture.loadFromImage(*characterImage);		//loads image to texture
	printf("Character::Character(): after texture.loadFromImage(sf::Image)");
	// Create a sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
//*/	//sprite.setColor(sf::Color(151, 251, 151, 255));
//	sprite.setPosition(10, 10);

/*
	characterPosX = 10;
	characterPosY = 10;
//*/
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
	printf("Character::initCharacter(): before texture.loadFromImage(sf::Image)\n");
	texture.loadFromImage(*characterImage);
	printf("Character::initCharacter(): after texture.loadFromImage(sf::Image)\n");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
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
 * @bug What is the intention of this function?
 * What it does is not even remotely connected to what it's named
 */
void Character::updatePosition()
{
//	std::cout<< "X-position: " << characterPosX << "\n";
//	std::cout<< "Y-position: " << characterPosY << "\n";
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
//		sprite.setTextureRect(sf::IntRect(0, 51, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		characterDirectionX = 1.0;
//		sprite.move(1.0, 0.0);
//		characterPosX++;
//		updatePosition();
//		sprite.setTextureRect(sf::IntRect(0, 17, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		characterDirectionY = -1.0;
//		sprite.move(0.0, -1.0);
//		characterPosY--;
//		updatePosition();
//		sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		characterDirectionY = 1.0;
//		sprite.move(0.0, 1.0);
//		characterPosY++;
//		updatePosition();
//		sprite.setTextureRect(sf::IntRect(0, 34, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::S)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		MineFactory *mineFactory;
		mineFactory = mineFactory->getMineFactory();

		if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		{
			mineFactory->getMine();
			std::cout<< "Mine placed\n";
		}
	}

}

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

}
