/*
 * main file for the Frank imt3601 project
 */ 
#include "Includes.hpp"

int main(int argc, char **argv)
{
	sf::Window app(sf::VideoMode(800,600,32),"testWindow");
	bool running = true;
	while (running)
	{
		app.display();
		
	}
	return EXIT_SUCCESS;
}
