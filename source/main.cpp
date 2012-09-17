/*
 * main file for the Frank imt3601 project
 */
#include "Includes.hpp"

int main(int argc, char **argv)
{

	const int MAPSIZEX = 15;
	const int MAPSIZEY = 15;
	
	sf::Window gameScreen(sf::VideoMode(800,600,32),"testWindow");

	
	Character player1; //error when loading image
	//player1.draw(&app);

	while (gameScreen.isOpen())
	{
		gameScreen.display();


		// Process events
        sf::Event event;
        
		while (gameScreen.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
			{
				gameScreen.close();
			}
         }
	}
	return EXIT_SUCCESS;
}
