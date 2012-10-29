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
	text.setString("Press 'L' for Local Play \nPress 'N' for networkplay");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Blue);
	text.setPosition(10,200);

	title.setString("Frank Darkhawk's MAZE!!!");
	title.setFont(font);
	title.setCharacterSize(30);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Blue);
	title.setPosition(200,0);

};

/**
* @brif: change old menu text into new menu text
* @param std::string text: The new text
* @return True on succses
*/
bool Menu::changeText(std::string text)
{
	Menu::text.setString(text);
	return true;
};

/**
* @brif: Menu Loop 
*/
void Menu::runMenu()
{
	menuOpen = true;
	changeText("Press 'L' for Local Play \nPress 'N' for networkplay");
	while(menuOpen)
	{
		draw();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			SelectNumberOfCharacters();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
			menuOpen = false;
		}
		
	}
};

/**
* @brif: Select number of players in the game
* @return The number of players
*/
int  Menu::SelectNumberOfCharacters()
{
	numOfPlayers = 0;
	std::string numOfPlayersText;
	std::string menutext;
	while(menuOpen)
	{
		numOfPlayersText=(char)(numOfPlayers+48);
		menutext = "Number of characters: ";
		menutext.insert((menutext.size()),numOfPlayersText);
		draw();
		changeText(menutext);
		draw();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			initplayers();
			menuOpen = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			numOfPlayers++;
			if (10 == numOfPlayers)
			{
				numOfPlayers = 9;
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			numOfPlayers--;
			if ((-1) == numOfPlayers)
			{
				numOfPlayers = 0;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
			menuOpen = false;
		}
	}
	return numOfPlayers;
};

bool Menu::initplayers()
{
	int i;

	World *world;
	world = world->getWorld();
	//if (argv[1]) {
	//	world->initMap(argv[1]);
	//}
	//else
	//{
		world->initMap((char *)"map/maptwo.txt");
	//}

	printf("main(int,char**): has got World, getting MineFactory\n");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();

	printf("main(int,char**): has got MineFactory, getting CharacterFactory\n");
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();

	
	
	for (i=0; i<numOfPlayers; i++)
	{
		printf("main(int,char**): has got CharacterFactory, getting player%d\n",i);
		Character *player1 = characterFactory->getCharacter(0);				// 0 for local-player character
		world->placeCharacter(player1);
	}
	return true;
};


/**
* @brif: Draw menu to screen.
*/
void Menu::draw()
{
	window->draw(sprite);
	window->draw(title);
	window->draw(text);
	window->display();
};
