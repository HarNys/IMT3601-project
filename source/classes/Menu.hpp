#ifndef __MENU__HEADER__GUARD__
#define __MENU__HEADER__GUARD__

#include "../Includes.hpp"

class Menu
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image *meunImage;
public:
	Menu(std::string fileLocation, int xPosTopLeftCorner, int yPosTopLeftCorner);
	void draw(sf::RenderWindow *window);
};


#endif //__MENU__HEADER__GUARD__
