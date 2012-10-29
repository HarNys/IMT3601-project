/**
 * Main file for the Neuton imt3601 project
 */
#include "Includes.hpp"

int main(int argc, char **argv)
{
	/**
	 * @todo make mapsizes parsed from arguments.
	 * @todo make System.{c,h}pp (maybe call it init?)
	 * @todo clean up int main(int,char**), move things where they
	 * 	should be(this depends of course on that the rest of
	 * 	the system is ready).
	 */
	sf::RenderWindow screen;
	screen.create(sf::VideoMode(800,600,32),"Neuton presents: Frank Darkhawks Maze RPG!");

/*
	char fullscreenoption;
	std::cout << "play in fullscreen? (Y/n)";
	std::cin >> fullscreenoption;

	if (fullscreenoption == 'n' || fullscreenoption == 'N')
	{
		screen.create(sf::VideoMode(800,600,32),"Neuton presents: Frank Darkhawks Maze RPG!");
	}
	else
	{
		int screenWith;
		int ScreenHight;
		std::cout << "what resolution do you like to have? example: 800 600 \n";
		std::cin >> screenWith;
		std::cin >> ScreenHight;

		screen.create(sf::VideoMode(screenWith,ScreenHight,32),"Neuton presents: Frank Darkhawks Maze RPG!",sf::Style::Fullscreen);
	}
//*/
	screen.setFramerateLimit(20);
	printf("main(int,char**): before getting singletons {World, MineFactory, CharacterFactory}\n");
	
	
	Menu* mainMenu = new Menu("img/Menu.gif",0,0);

	while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::L)))
	{
		mainMenu->draw(&screen);
	}
	
	
	World *world;
	world = world->getWorld();
	if (argv[1]) {
		world->initMap(argv[1]);
	}
	else
	{
		world->initMap((char *)"map/maptwo.txt");
	}

	printf("main(int,char**): has got World, getting MineFactory\n");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();

	printf("main(int,char**): has got MineFactory, getting CharacterFactory\n");
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();

	printf("main(int,char**): has got CharacterFactory, getting player1\n");
	Character *player1 = characterFactory->getCharacter(0);				// 0 for local-player character
	world->placeCharacter(player1);

	//Character *player5 = characterFactory->getCharacter(1);				// 1 none-playercharacter.
	//world->placeCharacter(player5);

	printf("main(int,char**): has got all singletons and player1\nmain(int,char**): starting gameloop\n");
	while (screen.isOpen())
	{
		world->update();
		screen.clear();
		world->draw(&screen);
//		player1->draw(&screen);
		screen.display();

		// Process events
		sf::Event event;

		/// @todo add escape as exit button

		while (screen.pollEvent(event))
		{
			player1->useController(event, player1);
			//player1->characterInput(event);

			// Close window : exit
			if (event.type == sf::Event::Closed)
			{
				world->~World();

				/// @bug program segfaults in here, commented
				///	out temporarily
				//mineFactory->~MineFactory();

				screen.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				if(event.KeyReleased && event.key.code == sf::Keyboard::P)
				{
					world->reset();
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
