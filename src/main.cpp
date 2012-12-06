/**
 * Main file for the Neuton imt3601 project
 */
#include "Includes.hpp"

int main(int argc, char **argv)
{
	/**
	 * All options possible for configuration should
	 * be in this struct.
	 *
	 * Howto add new options:
	 * \li Define variable in confSettings struct.
	 * \li Add default initialization right before
	 *	'Close configuration file after writing and setting defaults'
	 * \li Add file initialization at 'set variables'
	 */
	struct
	{
		int screenwidth;
		int screenheight;
		bool fullscreen; //!> fullscreen the application if true
	} confSettings;
	// Reading configuration file, if there is one
	FILE *configFile;
	configFile = fopen("game.ini", "r");//std::fstream::in | std::fstream::out);
	if (configFile == NULL)
	{
		perror("main(int,char**): Could not open configuration file 'game.ini'");
		printf("main(int,char**): Writing default configuration file 'game.ini' \n");
		configFile = fopen("game.ini", "w");
		// generate file from defaults
		fprintf(configFile,"# Configuration file for Frank Darkhawk's Amazing Maze rpg\n");
		confSettings.screenwidth = 800;
		fprintf(configFile,"screenwidth %d\n", confSettings.screenwidth);
		confSettings.screenheight = 600;
		fprintf(configFile,"screenheight %d\n", confSettings.screenheight);
		confSettings.fullscreen = false;
		fprintf(configFile,"fullscreen %d\n", confSettings.fullscreen);

		// Close configuration file after writing and setting defaults
		fclose(configFile);
	}
	else
	{
		printf("main(int,char**): Reading configuration file 'game.ini' \n");
		// set variables
		char variableBuffer[256];
		int valueBuffer = 0;
		while (!feof(configFile))
		{
			fscanf(configFile, "%s %d\n", variableBuffer, &valueBuffer);
			if (strchr(variableBuffer, '#'))
			{
				char seeker;
				do
				{
					seeker = fgetc(configFile);
				}
				while (seeker != '\n');
			}
			else if (!strcmp(variableBuffer, "screenwidth"))
			{
				confSettings.screenwidth = valueBuffer;
			}
			else if (!strcmp(variableBuffer, "screenheight"))
			{
				confSettings.screenheight = valueBuffer;
			}
			else if (!strcmp(variableBuffer, "fullscreen"))
			{
				confSettings.fullscreen = valueBuffer;
			}
			else
			{
				printf("main(int,char**): Variable '%s' not recognized \n", variableBuffer);
			}
		}
		printf("main(int,char**): Current configuration: \n");
		fprintf(stdout,"main(int,char**): screenwidth %d\n", confSettings.screenwidth);
		fprintf(stdout,"main(int,char**): screenheight %d\n", confSettings.screenheight);
		fprintf(stdout,"main(int,char**): fullscreen %d\n", confSettings.fullscreen);
	}

	#ifdef _OPENMP
	{
		omp_set_num_threads(10);
		int num_threads = 0;
		num_threads = omp_get_num_threads();
		printf("Number of threads: %d \n",num_threads);
		//omp_set_num_threads(num_threads/2);
	}
	#endif //_OPENMP

	/**
	 * @todo make mapsizes parsed from arguments.
	 * @todo make System.{c,h}pp (maybe call it init?)
	 * @todo clean up int main(int,char**), move things where they
	 * 	should be(this depends of course on that the rest of
	 * 	the system is ready).
	 */

	sf::RenderWindow screen;
	sf::Music music;
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
			sf::Event event;

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
						music.stop();
						mainMenu->runMenu();
					}
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
