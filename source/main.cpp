/*
 * main file for the Frank imt3601 project
 */
#include "Includes.hpp"

int main(int argc, char **argv)
{
	/**
	 * @todo make mapsizes parsed from arguments.
	 * @todo make System.{c,h}pp (maybe call it init?)
	 */
//	const int MAPSIZEX = 15;
//	const int MAPSIZEY = 15;
	sf::RenderWindow app(sf::VideoMode(800,600,32),"testWindow");
//	bool running = true;
	Character *player1 = new Character; //error when loading image
	

	while (app.isOpen())
	{
		app.display();


		// Process events
        sf::Event event;

		while (app.pollEvent(event))
        {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player1->characterMovementLeft();
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player1->characterMovementRight();
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player1->characterMovementUp();
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player1->characterMovementDown();
			}
			player1->draw(&app);
            // Close window : exit
            if (event.type == sf::Event::Closed)
			{
				app.close();
			}
         }
	}
	return EXIT_SUCCESS;
}
