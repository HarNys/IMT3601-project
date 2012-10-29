#include "../Includes.hpp"


Menu::Menu(std::string fileLocation, int xPosTopLeftCorner, int yPosTopLeftCorner)
{
	meunImage = new sf::Image;
	if ((*meunImage).loadFromFile(fileLocation))
	{
		printf("Character::initImage(): loaded img/Menu.gif\n");
	}
	else
	{

		printf("Character::initImage(): could not load image "
			"'img/menu.png'\n");
	}

	texture.loadFromImage(*meunImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sprite.setPosition(xPosTopLeftCorner,yPosTopLeftCorner);

};
void Menu::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
};