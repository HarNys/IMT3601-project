#ifndef __MENU__HEADER__GUARD__
#define __MENU__HEADER__GUARD__

#include "../Includes.hpp"

class Menu
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image *menuImage;
	sf::Font font;
	sf::Text title;
	sf::Text text;
	sf::RenderWindow* window;
	int numOfPlayers;
	bool menuOpen;
	
public:
	Menu(sf::RenderWindow* renderWindow);
	void draw();
	bool changeText(std::string text);
	void runMenu();
	int  SelectNumberOfCharacters();
	bool initplayers();

};


#endif //__MENU__HEADER__GUARD__
