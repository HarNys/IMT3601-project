#include "../Includes.hpp"


Menu::Menu(std::string fileLocation, int xPosTopLeftCorner, int yPosTopLeftCorner)
{
	menuImage = new sf::Image;
	if ((*menuImage).loadFromFile(fileLocation))
	{
		printf("Menu::Menu(std::string,int,int): loaded 'img/Menu.gif'\n");
	}
	else
	{
		printf("Menu::Menu(std::string,int,int): could not load image "
			"'img/Menu.gif'\n");
	}

	texture.loadFromImage(*menuImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
	sprite.setPosition(xPosTopLeftCorner,yPosTopLeftCorner);

};
void Menu::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
};
