
#include "../Includes.hpp"

Character::Character()
{
	
	
	sf::Image image;
	image.loadFromFile("img\player.gif");
	texture.loadFromImage(image);

	// Create a sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);
	
	characterPosX = 0;
	characterPosY = 0;
};

void Character::draw(sf::RenderWindow *window)
{
	 //Draw
	//window->draw(sprite);
};