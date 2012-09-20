
#include "../Includes.hpp"

Character::Character()
{
	sf::Image image;
	/// @bug this path is not correct in windows for some reason
	image.loadFromFile("img/player.gif");
	texture.loadFromImage(image);

	// Create a sprite
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 10, 10));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(10, 10);


	characterPosX = 10;
	characterPosY = 10;
};

void Character::draw(sf::RenderWindow *window)
{
	//Draw
	window->draw(sprite);
};


void Character::characterMovementLeft()
{

	sprite.move(-1.0, 0.0);
	characterPosX--;
	updatePosition();
};

void Character::characterMovementRight()
{
	sprite.move(1.0, 0.0);
	characterPosX++;
	updatePosition();
};

void Character::characterMovementUp()
{
	sprite.move(0.0, -1.0);
	characterPosY--;
	updatePosition();
};

void Character::characterMovementDown()
{
	sprite.move(0.0, 1.0);
	characterPosY++;
	updatePosition();
};

void Character::updatePosition()
{
	std::cout<< "X-position: " << characterPosX << "\n";
	std::cout<< "Y-position: " << characterPosY << "\n";
};

