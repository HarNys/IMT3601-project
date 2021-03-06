/*
 * Menu.cpp
 *
 * Copyright 2012 Harry Nystad <harry.ny@live.no>
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
#include "../Includes.hpp"

/**
 * initialise the menu, sets up the text (size, color, etc), sprite for background and loads in the music for the menu.
 */
Menu::Menu(sf::RenderWindow* renderWindow)
{
	window = renderWindow;
	menuOpen = true;
	numOfPlayers = 0;
	imageCount = 0;
	int textHight = 200;
	//imageCountY = 1; // Not used.
	gameRuning = false;

	menuImage = new sf::Image;
	if ((*menuImage).loadFromFile("img/Menu.gif"))
	{

		printf("Menu::Menu(std::string,int,int): loaded 'img/menu.gif'\n");
	}
	else
	{
		printf("Menu::Menu(std::string,int,int): could not load image "
			"'img/menu.gif'\n");
	}

	texture.loadFromImage(*menuImage);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
	sprite.scale(11.59,8.57);
	sprite.setPosition(0,0);


	if(font.loadFromFile("font/promethean.ttf"))
	{
		printf("Success on loading font \n");
	}

	// Create a title
	title.setString("Frank Darkhawk's MAZE!!!");
	title.setFont(font);
	title.setCharacterSize(30);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Green);
	title.setPosition(200,0);

	// Create a text
	textLineOne.setString("Singleplayer");
	textLineOne.setFont(font);
	textLineOne.setCharacterSize(30);
	textLineOne.setStyle(sf::Text::Bold);
	textLineOne.setColor(sf::Color::Green);
	textLineOne.setPosition(250,200);
	textHight += 40;

	textLineTwo.setString("Multiplayer");
	textLineTwo.setFont(font);
	textLineTwo.setCharacterSize(30);
	textLineTwo.setStyle(sf::Text::Bold);
	textLineTwo.setColor(sf::Color::Green);
	textLineTwo.setPosition(250,textHight);
	textHight += 40;

	exit.setString("Exit");
	exit.setFont(font);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Bold);
	exit.setColor(sf::Color::Green);
	exit.setPosition(250,textHight);


	// Open music from an audio file
	if (!gameMusic.openFromFile("music/Circuit_Soldiers-Intellectual_Property_is_a_Dying_Whore.ogg"))
	{
		printf("main(int argc, char **argv): Can't load music");
	}
	else
	{
		gameMusic.setVolume(50);         // reduce the volume
		gameMusic.setLoop(true);         // make it loop
	}
	if (!menuMusic.openFromFile("music/Circuit_Soldiers-The_Night_before_Battle.ogg"))
	{
		printf("Menu::Menu(sf::RenderWindow* renderWindow): can't load music");
	}
	else
	{
		menuMusic.setVolume(50);         // reduce the volume
		menuMusic.setLoop(true);         // make it loop
	}
    menuMusic.play();
};

/**
 * @brief change old menu text into new menu text
 * @param text The new text
 * @return True on succses
 */
bool Menu::changeText(std::string text)
{
	Menu::textLineOne.setString(text);
	return true;
}

/**
 * Displays a menu screen where the layer can pick singelplayer, multiplayer or exit the game
 *
 * @todo Rename imageCount.
 * @todo Give '69' a variable.
 * @todo Fix keyboard polling.
 */
void Menu::runMenu()
{
	gameMusic.stop();
	menuMusic.play();

	textLineOne.setString("Singleplayer");
	textLineTwo.setString("Multiplayer");
	exit.setString("Exit");
	menuOpen = true;
	int menuItem = 0;


	while(menuOpen)
	{
		sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
		mainDraw();
		sf::Event event;
		window->setKeyRepeatEnabled(false);

        while(window->pollEvent(event))
        {
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					menuItem --;
					if (menuItem < 0)
					{
						menuItem = 0;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::S)
				{
					menuItem ++;
					if (menuItem > 2)
					{
						menuItem = 2;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					if(gameRuning)
					{
						menuOpen = false;
					}
				}

			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::E)
				{
					switch(menuItem)
					{
					case 0:
						{
							SelectNumberOfCharacters();
							break;
						}
					case 1:
						{
							networking();
							break;
						}
					case 2:
						{
							menuMusic.stop();
							window->close();
							menuOpen = false;
							break;
						}
					}
				}
			}

			switch(menuItem)
			{
			case 0:
				{
					textLineOne.setColor(sf::Color::Yellow);
					textLineTwo.setColor(sf::Color::Green);
					exit.setColor(sf::Color::Green);
					break;
				}
			case 1:
				{
					textLineOne.setColor(sf::Color::Green);
					textLineTwo.setColor(sf::Color::Yellow);
					exit.setColor(sf::Color::Green);
					break;
				}
			case 2:
				{
					textLineOne.setColor(sf::Color::Green);
					textLineTwo.setColor(sf::Color::Green);
					exit.setColor(sf::Color::Yellow);
					break;
				}
			}
		}

		animation();
	}

}

/**
* @brief Select number of players in the game
* @return The number of players
*/
int  Menu::SelectNumberOfCharacters()
{
	numOfPlayers = 0;
	std::string numOfPlayersText;
	std::string menutext;
	sf::Event event;
	bool running = true;

	//while this part of the menu is running
	while(running)
	{
		window->setKeyRepeatEnabled(false);

		numOfPlayersText=(char)(numOfPlayers+48);
		menutext = "Number of AI: ";
		menutext.insert((menutext.size()),numOfPlayersText);

		changeText(menutext);
		sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
		localDraw();
		sf::Event event;

		while (window->pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::E)
				{
					initplayers();
					running = false;
					menuOpen = false;
				}
				else if(event.key.code == sf::Keyboard::W)
				{
					numOfPlayers++;
					if (10 == numOfPlayers)
					{
						numOfPlayers = 9;
					}
				}
				else if(event.key.code == sf::Keyboard::S)
				{
					numOfPlayers--;
					if ((-1) == numOfPlayers)
					{
						numOfPlayers = 0;
					}
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					running = false;
					textLineOne.setString("Singleplayer");
					textLineTwo.setString("Multiplayer");
					exit.setString("Exit");
				}
			}
		}
		animation();
	}
	return numOfPlayers;
}

/**
 * Displays a screen where the player can write in an ip address for
 * netowrking
 */
void Menu::networking()
{
	sf::Event event;
	std::string ip;
//	int ipLength = 0; // Not currently used.
	bool running = true;

	window->setKeyRepeatEnabled(false);
	ip = "";
	textLineOne.setString("ip address:");

	//while this part of the menu is running
	while(running)
	{
		sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
		networkDraw();
		while(window->pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Num1)
				{
					ip.insert((ip.size()),"1");
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					ip.insert((ip.size()),"2");
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					ip.insert((ip.size()),"3");
				}
				else if (event.key.code == sf::Keyboard::Num4)
				{
					ip.insert((ip.size()),"4");
				}
				else if (event.key.code == sf::Keyboard::Num5)
				{
					ip.insert((ip.size()),"5");
				}
				else if (event.key.code == sf::Keyboard::Num6)
				{
					ip.insert((ip.size()),"6");
				}
				else if (event.key.code == sf::Keyboard::Num7)
				{
					ip.insert((ip.size()),"7");
				}
				else if (event.key.code == sf::Keyboard::Num8)
				{
						ip.insert((ip.size()),"8");
				}
				else if (event.key.code == sf::Keyboard::Num9)
				{
					ip.insert((ip.size()),"9");
				}
				else if (event.key.code == sf::Keyboard::Num0)
				{
						ip.insert((ip.size()),"0");
				}
				else if (event.key.code == sf::Keyboard::Period)
				{
					ip.insert((ip.size()),".");
				}
				else if (event.key.code == sf::Keyboard::Back)
				{
					if (ip.size() > 0)
					{
						ip.resize(ip.size()-1);
					}
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					running = false;

				}
			}
			//check the size of ip address
			if(ip.size() > 15)
			{
				ip.resize(15);
			}
			textLineTwo.setString(ip);
		}
	animation();
	}
	textLineOne.setString("Singleplayer");
	textLineTwo.setString("Multiplayer");
	exit.setString("Exit");
}

/**
 * Resets World and then sets up a new one and adds characters to it
 */
bool Menu::initplayers()
{
	int i;
	World *world;
	world = world->getWorld();

	if(gameRuning)
	{
		world->reset();
	}

	world->initMap((char *)"map/maptwo.txt");
	world->randomGenerate(true);

	printf("Menu::initplayers(): has got World, getting MineFactory\n");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();

	printf("Menu::initplayers(): has got MineFactory, getting CharacterFactory\n");
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();

	// This was comented out to just have npc's running around
//*/
	printf("Menu::initplayers(): has got CharacterFactory, getting player \n");
	Character *player = characterFactory->getCharacter();
	player->setCharacterType(0); // 0 for local-player character
	player->setID(0);
	world->placeCharacter(player);//*/

	Character *npc;

	for (i=0; i<numOfPlayers; i++)
	{
		printf("main(int,char**): has got CharacterFactory, getting NPC %d\n",i);
		npc = characterFactory->getCharacter();
		npc->setCharacterType(1);
		npc ->setID(i+1);
		world->placeCharacter(*npc);
	}
	printf("Menu::initplayers(): Menu all done \n");
	window->setKeyRepeatEnabled(true);
	gameRuning = true;
	menuMusic.stop();
	return true;
}

/**
 * This fuction is used to select the next frame in the animation of the planet in the background.
 * every 0.5 sec the fram is changing and loops back to fram 0 after fram 12 is displayed
 * @todo This does not draw the animation from multiplayer-menu.
 */
void Menu::animation()
{
	int curentTime = timer.getElapsedTime().asMilliseconds();
	printf("timer is: %d \r",curentTime);
	curentTime = timer.getElapsedTime().asMilliseconds();

	if(curentTime > 50)
	{
		timer.restart();
		imageCount ++;

		if(imageCount >12)
		{
			imageCount = 0;
		}
	}
}



/**
* @brief Draw main menu to screen.
*/
void Menu::mainDraw()
{
	window->draw(sprite);
	window->draw(title);
	window->draw(textLineOne);
	window->draw(textLineTwo);
	window->draw(exit);
	window->display();
}

/**
* @brief Draw singleplayer part of menu to screen.
*/
void Menu::localDraw()
{
	window->draw(sprite);
	window->draw(title);
	window->draw(textLineOne);
	window->display();
}

/**
* @brief Draw netowk part of menu to screen.
*/
void Menu::networkDraw()
{

	window->draw(sprite);
	window->draw(title);
	window->draw(textLineOne);
	window->draw(textLineTwo);
	window->display();
}
