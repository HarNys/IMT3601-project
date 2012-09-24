
#include "../Includes.hpp"

Character::Character()
{
	sf::Image image;
	/// @bug this path is not correct in windows for some reason
	//image.loadFromFile("img\player.png");
	texture.loadFromImage(image);

	// Create a sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(10, 10);


	characterPosX = 10;
	characterPosY = 10;

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

//movement-functions
//checks if the key is pressed and then released
//to reset characterDirectionX/Y
void Character::characterInput(sf::Event e)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		characterDirectionX = -1.0;
		sprite.move(-1.0, 0.0);
		characterPosX--;
		updatePosition();
		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		characterDirectionX = 1.0;
		sprite.move(1.0, 0.0);
		characterPosX++;
		updatePosition();
		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		characterDirectionY = -1.0;
		sprite.move(0.0, -1.0);
		characterPosY--;
		updatePosition();
		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		characterDirectionY = 1.0;
		sprite.move(0.0, 1.0);
		characterPosY++;
		updatePosition();
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
