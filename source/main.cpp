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

	
	World *world;
	world = world->getWorld();

/*	printf("before world->getWorld()");
	World *world;
	world = world->getWorld();

	printf("after world->getWorld()\nbefore mineFactory->getMineFactory");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();
	printf("after mineFactory->getMineFactory()");
//*/

	/// Makes two characters, only one is used at this point (player1)
	/// @todo Have the characterfactory return more than just one player 
	CharacterFactory* characterFactory;
	characterFactory = characterFactory->getCharacterFactory();
	Character *player1 = characterFactory->getCharacter(); //error when loading image
	

	while (screen.isOpen())
	{
		screen.display();


		// Process events
		sf::Event event;

		/// @todo add escape as exit button

		while (screen.pollEvent(event))
		{

			player1->characterInput(event);
			screen.clear();
			player1->draw(&screen);
			world->draw(&screen);
			// Close window : exit
			if (event.type == sf::Event::Closed)
			{
				
				world->~World();

/*				MineFactory *mineFactory;
				mineFactory = mineFactory->getMineFactory();
				mineFactory->~MineFactory();
//*/
				screen.close();
			}
		}
	}
	return EXIT_SUCCESS;
}