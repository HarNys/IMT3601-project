/**
 * Main file for the Neuton imt3601 project
 */
#include "Includes.hpp"

// Alias the program_options namespace into progopt:
namespace progopt = boost::program_options;

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
	sf::Music music;
//	screen.create(sf::VideoMode(800,600,32),"Neuton presents: Frank Darkhawks Maze RPG!");

	/**
	 * Boost program_options.
	 * The program_options library does some overly complex stuff
	 * with operators, don't spend time understanding how it works
	 * (if you really want to know see the design document or ask
	 *  jayson).
	 *
	 * If you are going to use it, look at examples, tutorial and
	 * sources.
	 */
	std::string configFile;
	progopt::options_description gameIni("game.ini options");
	gameIni.add_options()
		("config,c", progopt::value<std::string>(&configFile)->default_value("game.ini"), "name/path of configuration file.")
		;
	// Add options to commandline
	progopt::options_description cmdline_options;
	cmdline_options.add(generic);
	// Add options to configuration file
	progopt::options_description config_file_options;
	config_file_options.add(generic);

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

	Menu* mainMenu = new Menu(&screen);
	mainMenu->runMenu();



	World *world;
	world = world->getWorld();
	//if (argv[1]) {
	//	world->initMap(argv[1]);
	//}
	//else
	//{
	//	world->initMap((char *)"map/maptwo.txt");
	//}

		// Open it from an audio file
	if (!music.openFromFile("music/Circuit_Soldiers-Intellectual_Property_is_a_Dying_Whore.ogg"))
	{
		printf("main(int argc, char **argv): can't load music");
	}
	else
	{
		music.setVolume(50);         // reduce the volume
		music.setLoop(true);         // make it loop
		music.play();
	}

	printf("main(int,char**): has got all singletons and player1\nmain(int,char**): starting gameloop\n");
	while (screen.isOpen())
	{

		{


			world->update();
			screen.clear();
			world->draw(&screen);
	//		player1->draw(&screen);
			screen.display();

			// Process events
			sf::Event event; // why is this in the game loop?

			/// @todo add escape as exit button

			while (screen.pollEvent(event))
			{

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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					if(event.KeyReleased && event.key.code == sf::Keyboard::Escape)
					{
						world->reset();
						music.stop();
						mainMenu->runMenu();
					}
				}
			}
		}
	}
	return EXIT_SUCCESS;
}