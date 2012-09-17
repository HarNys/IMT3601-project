
#include "../Includes.hpp"

Character::Character()
{
<<<<<<< HEAD
	
	
	sf::Image image;
	image.loadFromFile("img\player.gif");
	texture.loadFromImage(image);

	// Create a sprite
=======

	// Declare and load a texture

	texture.loadFromFile("img/player");

	// Create a sprite

>>>>>>> 8b99fe17df72d34bc3e4a3ccbbe3e591ba35131e
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
	sprite.setColor(sf::Color(255, 255, 255, 200));
	sprite.setPosition(100, 25);
<<<<<<< HEAD
	
	characterPosX = 0;
	characterPosY = 0;
=======

	//*/
	posX = 0;
	posY = 0;
>>>>>>> 8b99fe17df72d34bc3e4a3ccbbe3e591ba35131e
};

void Character::draw(sf::RenderWindow *window)
{
<<<<<<< HEAD
	 //Draw
	//window->draw(sprite);
};
=======
	// Draw it
	//window.draw(sprite);
};
>>>>>>> 8b99fe17df72d34bc3e4a3ccbbe3e591ba35131e
