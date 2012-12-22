/*
 * Menu.hpp
 *
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

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
//	int imageCountY; // Not used
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
	void animation();

};


#endif //__MENU__HEADER__GUARD__
