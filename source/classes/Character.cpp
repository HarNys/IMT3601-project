
#include "../Includes.hpp"


Character::Character()
{
	
	// Declare and load a texture
	
	texture.loadFromFile("img/player");

	// Create a sprite
	
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);
	//*/
	posX = 0;
	posY = 0;
};

void Character::draw()
{
	// Draw it
	//window.draw(sprite);
};