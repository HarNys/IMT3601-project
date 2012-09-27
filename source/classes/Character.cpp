
#include "../Includes.hpp"

Character::Character()
{
	sf::Image image;
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
	texture.loadFromImage(image);		//loads image to texture
	//createMaskFromColor

	// Create a sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
	//sprite.setColor(sf::Color(151, 251, 151, 255));
	sprite.setPosition(10, 10);


	characterPosX = 10;
	characterPosY = 10;
//*/
	characterDirectionX = 0;
	characterDirectionY = 0;
};

void Character::draw(sf::RenderWindow *window)
{
	//Draw
	window->draw(sprite);
};

void Character::updatePosition()
{
	std::cout<< "X-position: " << characterPosX << "\n";
	std::cout<< "Y-position: " << characterPosY << "\n";
};

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @todo comment parameter
void Character::characterInput(sf::Event e)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		characterDirectionX = -1.0;
		sprite.move(-1.0, 0.0);
		characterPosX--;
		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 51, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		characterDirectionX = 1.0;
		sprite.move(1.0, 0.0);
		characterPosX++;
		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 17, 15, 15));
		
		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		characterDirectionY = -1.0;
		sprite.move(0.0, -1.0);
		characterPosY--;
		updatePosition();
		sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		characterDirectionY = 1.0;
		sprite.move(0.0, 1.0);
		characterPosY++;
		updatePosition();
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
			mineFactory->getMine();
			std::cout<< "Mine placed\n";
		}
	}

}

void Character::placeMine(sf::Event e)
{
	 MineFactory *mineFactory;
	 mineFactory = mineFactory->getMineFactory();

}
