#include "../Includes.hpp"


Menu::Menu(sf::RenderWindow* renderWindow)
{
	window = renderWindow;
	menuOpen = true;
	numOfPlayers = 0;
	imageCount = 0;
	//imageCountY = 1;

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

	// Create a text
	localPlay.setString("Singleplayer");
	localPlay.setFont(font);
	localPlay.setCharacterSize(30);
	localPlay.setStyle(sf::Text::Bold);
	localPlay.setColor(sf::Color::Green);
	localPlay.setPosition(250,200);

	networkPlay.setString("Multiplayer");
	networkPlay.setFont(font);
	networkPlay.setCharacterSize(30);
	networkPlay.setStyle(sf::Text::Bold);
	networkPlay.setColor(sf::Color::Green);
	networkPlay.setPosition(250,240);

	exit.setString("Exit");
	exit.setFont(font);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Bold);
	exit.setColor(sf::Color::Green);
	exit.setPosition(250,280);

	title.setString("Frank Darkhawk's MAZE!!!");
	title.setFont(font);
	title.setCharacterSize(30);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Green);
	title.setPosition(200,0);

	// Open it from an audio file
	if (!music.openFromFile("music/Circuit_Soldiers-The_Night_before_Battle.ogg"))
	{
		printf("Menu::Menu(sf::RenderWindow* renderWindow): can't load music");
	}
	else
	{
		music.setVolume(50);         // reduce the volume
		music.setLoop(true);         // make it loop
	}

};

/**
* @brif: change old menu text into new menu text
* @param std::string text: The new text
* @return True on succses
*/
bool Menu::changeText(std::string text)
{
	Menu::localPlay.setString(text);
	return true;
};

/**
* @brif: Menu Loop
*/
void Menu::runMenu()
{
	music.play();
	localPlay.setString("Singleplayer");
	networkPlay.setString("Multiplayer");
	exit.setString("Exit");
	menuOpen = true;
	int menuItem = 0;


	while(menuOpen)
	{
		sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
		mainDraw();
		sf::Event event;
		window->setKeyRepeatEnabled(false);
		window->pollEvent(event);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::W)
			{
				menuItem --;
				if (menuItem < 0)
				{
					menuItem = 0;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::S)
			{
				menuItem ++;
				if (menuItem > 2)
				{
					menuItem = 2;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::E)
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
						break;
					}
				case 2:
					{
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
				localPlay.setColor(sf::Color::Yellow);
				networkPlay.setColor(sf::Color::Green);
				exit.setColor(sf::Color::Green);
				break;
			}
		case 1:
			{
				localPlay.setColor(sf::Color::Green);
				networkPlay.setColor(sf::Color::Yellow);
				exit.setColor(sf::Color::Green);
				break;
			}
		case 2:
			{
				localPlay.setColor(sf::Color::Green);
				networkPlay.setColor(sf::Color::Green);
				exit.setColor(sf::Color::Yellow);
				break;
			}
		}

		int curentTime = timer.getElapsedTime().asMilliseconds();
		printf("timer is: %d \r",curentTime);
		curentTime = timer.getElapsedTime().asMilliseconds();

		if(curentTime > 50)
		{
			timer.restart();
			curentTime = timer.getElapsedTime().asSeconds();
			imageCount ++;

			if(imageCount >12)
			{
				imageCount = 0;
			}
		}
	}

};

/**
* @brif: Select number of players in the game
* @return The number of players
* @todo: Stop keys from repeating.
*/
int  Menu::SelectNumberOfCharacters()
{
	numOfPlayers = 0;
	std::string numOfPlayersText;
	std::string menutext;
	sf::Event event;


	while(menuOpen)
	{
		window->setKeyRepeatEnabled(false);
		window->pollEvent(event);

		numOfPlayersText=(char)(numOfPlayers+48);
		menutext = "Number of AI: ";
		menutext.insert((menutext.size()),numOfPlayersText);

		changeText(menutext);
		sprite.setTextureRect(sf::IntRect(69*imageCount, 0, 69, 70));
		localDraw();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::E)
			{
				initplayers();
				menuOpen = false;
			}

		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::W)
			{
				numOfPlayers++;
				if (10 == numOfPlayers)
				{
					numOfPlayers = 9;
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if(event.KeyReleased && event.key.code == sf::Keyboard::S)
			{
				numOfPlayers--;
				if ((-1) == numOfPlayers)
				{
					numOfPlayers = 0;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			runMenu();
		}
		int curentTime = timer.getElapsedTime().asMilliseconds();
		printf("timer is: %d \r",curentTime);
		curentTime = timer.getElapsedTime().asMilliseconds();

		if(curentTime > 50)
		{
			timer.restart();
			curentTime = timer.getElapsedTime().asSeconds();
			imageCount ++;

			if(imageCount >12)
			{
				imageCount = 0;
			}
		}
	}
	return numOfPlayers;
};

bool Menu::initplayers()
{
	int i;

	World *world;
	world = world->getWorld();

	world->initMap((char *)"map/maptwo.txt");
	world->randomGenerate(true);

	printf("Menu::initplayers(): has got World, getting MineFactory\n");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();

	printf("Menu::initplayers(): has got MineFactory, getting CharacterFactory\n");
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();

	printf("Menu::initplayers(): has got CharacterFactory, getting player \n");
	Character *player = characterFactory->getCharacter();
	player->setCharacterType(0); // 0 for local-player character
	player->setID(0);
	world->placeCharacter(player);

	Character *npc;

	for (i=0; i<numOfPlayers; i++)
	{
		printf("main(int,char**): has got CharacterFactory, getting NPC %d\n",i);
		npc = characterFactory->getCharacter();
		npc->setCharacterType(1);
		npc ->setID(i+1);
		world->placeCharacter(npc);
	}
	window->setKeyRepeatEnabled(true);
	music.stop();
	return true;
};


/**
* @brif: Draw main menu to screen.
*/
void Menu::mainDraw()
{
	window->draw(sprite);
	window->draw(title);
	window->draw(localPlay);
	window->draw(networkPlay);
	window->draw(exit);
	window->display();
};

/**
* @brif: Draw singleplayer part of menu to screen.
*/
void Menu::localDraw()
{
	window->draw(sprite);
	window->draw(title);
	window->draw(localPlay);
	window->display();
};

/**
* @brif: Draw netowk part of menu to screen.
*/
void Menu::networkDraw()
{

};