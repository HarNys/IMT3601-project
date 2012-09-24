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
	sf::RenderWindow screen(sf::VideoMode(800,600,32),"Neuton presents: Frank Darkhawks Maze RPG!");

/*	printf("before world->getWorld()");
	World *world;
	world = world->getWorld();

	printf("after world->getWorld()\nbefore mineFactory->getMineFactory");
	MineFactory *mineFactory;
	mineFactory = mineFactory->getMineFactory();
	printf("after mineFactory->getMineFactory()");
//*/
	Character *player1 = new Character("Ninja"); //error when loading image

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
			// Close window : exit
			if (event.type == sf::Event::Closed)
			{
/*				World *world;
				world = world->getWorld();
				world->~World();

				MineFactory *mineFactory;
				mineFactory = mineFactory->getMineFactory();
				mineFactory->~MineFactory();
//*/
				screen.close();
			}
		}
	}
	return EXIT_SUCCESS;
}