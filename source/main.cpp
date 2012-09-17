/*
 * main file for the Frank imt3601 project
 */ 
#include "Includes.hpp"

int main(int argc, char **argv)
{
	sf::RenderWindow app(sf::VideoMode(800,600,32),"testWindow");
	bool running = true;
	//Character player1; //error when loading image
	//player1.draw(&app);

	while (running)
	{
		app.display();
		
	}
	return EXIT_SUCCESS;
}
