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
	sf::Text textLineOne;
	sf::Text textLineTwo;
	sf::Text exit;
	sf::RenderWindow* window;
	sf::Music music;
	int numOfPlayers;
	bool menuOpen;
	int imageCount;
	int imageCountY;
	bool gameRuning;
	sf::Clock timer;
	
public:
	Menu(sf::RenderWindow* renderWindow);
	void mainDraw();
	void localDraw();
	void networkDraw();
	bool changeText(std::string text);
	void runMenu();
	int  SelectNumberOfCharacters();
	bool initplayers();
	void networking();
	void aniamtion();

};


#endif //__MENU__HEADER__GUARD__
