/*
 * main file for the Frank imt3601 project
 */
#include "Includes.hpp"

int main(int argc, char **argv)
{
<<<<<<< HEAD
	sf::RenderWindow app(sf::VideoMode(800,600,32),"testWindow");
=======
	/**
	 * @todo make mapsizes parsed from arguments.
	 * @todo make System.{c,h}pp (maybe call it init?)
	 */
	const int MAPSIZEX = 15;
	const int MAPSIZEY = 15;
	sf::Window app(sf::VideoMode(800,600,32),"testWindow");
>>>>>>> 8b99fe17df72d34bc3e4a3ccbbe3e591ba35131e
	bool running = true;
	//Character player1; //error when loading image
	//player1.draw(&app);

	while (running)
	{
		app.display();
	}
	return EXIT_SUCCESS;
}
