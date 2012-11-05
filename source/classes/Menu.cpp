#include "../Includes.hpp"


Menu::Menu(sf::RenderWindow* renderWindow)
{
	window = renderWindow;
	menuOpen = true;
	numOfPlayers = 0;

	menuImage = new sf::Image;
	if ((*menuImage).loadFromFile("img/menu.gif"))
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
	sprite.setTextureRect(sf::IntRect(0, 0, menuImage->getSize().x, menuImage->getSize().y));
	sprite.setPosition(0,0);


	if(font.loadFromFile("font/arial.ttf"))
	{
		printf("Success on loading font \n");
	}

	// Create a text
	localPlay.setString("Singelplayer");
	localPlay.setFont(font);
	localPlay.setCharacterSize(30);
	localPlay.setStyle(sf::Text::Bold);
	localPlay.setColor(sf::Color::Black);
	localPlay.setPosition(250,200);

	networkPlay.setString("Multiplayer");
	networkPlay.setFont(font);
	networkPlay.setCharacterSize(30);
	networkPlay.setStyle(sf::Text::Bold);
	networkPlay.setColor(sf::Color::Black);
	networkPlay.setPosition(250,240);

	exit.setString("Exit");
	exit.setFont(font);
	exit.setCharacterSize(30);
	exit.setStyle(sf::Text::Bold);
	exit.setColor(sf::Color::Black);
	exit.setPosition(250,280);

	title.setString("Frank Darkhawk's MAZE!!!");
	title.setFont(font);
	title.setCharacterSize(30);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Black);
	title.setPosition(200,0);

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
	localPlay.setString("Singelplayer");
	networkPlay.setString("Multiplayer");
	exit.setString("Exit");
	menuOpen = true;
	//changeText("Press 'L' for Local Play \nPress 'N' for networkplay");
	int menuItem = 0;
	while(menuOpen)
	{
		mainDraw();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			menuItem --;
			if (menuItem < 0)
			{
				menuItem = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			menuItem ++;
			if (menuItem > 2)
			{
				menuItem = 2;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
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

		switch(menuItem)
		{
		case 0:
			{
				localPlay.setColor(sf::Color::White);
				networkPlay.setColor(sf::Color::Black);
				exit.setColor(sf::Color::Black);
				break;
			}
		case 1:
			{
				localPlay.setColor(sf::Color::Black);
				networkPlay.setColor(sf::Color::White);
				exit.setColor(sf::Color::Black);
				break;
			}
		case 2:
			{
				localPlay.setColor(sf::Color::Black);
				networkPlay.setColor(sf::Color::Black);
				exit.setColor(sf::Color::White);
				break;
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
		numOfPlayersText=(char)(numOfPlayers+48);
		menutext = "Number of AI: ";
		menutext.insert((menutext.size()),numOfPlayersText);

		changeText(menutext);
		localDraw();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			
				initplayers();
				menuOpen = false;
			
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			
			numOfPlayers++;
			if (10 == numOfPlayers)
			{
				numOfPlayers = 9;
			}	
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			numOfPlayers--;
			if ((-1) == numOfPlayers)
			{
				numOfPlayers = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			runMenu();
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

	printf("Menu::initplayers(): has got World, getting MineFactory\n");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();

	printf("Menu::initplayers(): has got MineFactory, getting CharacterFactory\n");
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();

	printf("Menu::initplayers(): has got CharacterFactory, getting player \n");
	Character *player = characterFactory->getCharacter();
	player->setCharacterType(1); // 0 for local-player character
	player ->setID(0);
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
* @brif: Draw singelplayer part of menu to screen.
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
