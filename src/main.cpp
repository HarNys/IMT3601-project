/*
 * main.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
 * Copyright 2012 rjan Rkkum Brandtzg <orokkum@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
/**
 * Main file for the Neuton imt3601 project
 */
#include "Includes.hpp"

void *chatserver(void *unused) // rename to reciever
{
	sf::UdpSocket socket;
	socket.bind(4444);
	bool quit = false;
	char buffer[1024];
	std::size_t received = 0;
	sf::IpAddress sender;
	unsigned short port;
	unsigned long count = 0;
	char *lastBuffer;
//	lastBuffer = (char *) malloc (sizeof (char) * 1024);
	while(!quit)
	{
//		printf ("ready to recieve");
		if (socket.Done == socket.receive(buffer, sizeof(buffer), received, sender, port)) 
		{
		//	if (!(lastBuffer == buffer))
			{
				count++;
				printf("%s said: %s, count: %lu\n", sender.toString().c_str(), buffer+1, count);
	//			lastBuffer = buffer;
			}
		printf ("if finished \n");	
	
		}
	//	std::string message = "Welcome " + sender.toString();
	//	socket.send(message.c_str(), message.size() + 1, sender, port);
	}
	return NULL;
}

void *chatclient(void *params) //rename to sender
{
	char * peerIp = (char*) params;
	
	sf::UdpSocket socket;
	socket.bind(4445);
	char *buffer;
	//std::size_t received = 0;
	//sf::IpAddress sender;
	//sender = "128.39.141.108";
	unsigned short port;
	bool quit = 0;
	unsigned long count = 0;
	World *world;
	world->getWorld();

	while (!quit)
	{
		std::string message = world->staticMapString(); //"Hi, I am " + sf::IpAddress::getLocalAddress().toString(); 
		socket.send(message.c_str(), message.size() + 1, peerIp, 4444);			
	//	printf ("hey %s \r", peerIp );
	//	socket.receive(buffer, sizeof(buffer), received, sender, port);			
	//	printf("%s said: %s, count: %lu\r",sender.toString().c_str() ,buffer, count++); 
	}
	return NULL;
}

int main(int argc, char **argv)
{
	/**
	 * All options possible for configuration should
	 * be in this struct.
	 *
	 * Howto add new options:
	 * \li Define variable in confSettings struct.
	 * \li Add default initialization right before
	 *	'Close configuration file after writing and
	 * 	 setting defaults'
	 * \li Add file initialization at 'set variables'
	 *
	 * Note that adding a new option requires either writing a new
	 * config file, or manually adding in the new option.
	 */
	struct
	{
		int screenwidth;
		int screenheight;
		bool fullscreen; // fullscreen the application if true
		bool isHost;
		bool chatOn;
		sf::IpAddress peerIp;
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
		confSettings.isHost = false;
		fprintf(configFile,"isHost %d\n", confSettings.isHost);
		confSettings.chatOn = true;
		fprintf(configFile,"isHost %d\n", confSettings.chatOn);
		confSettings.peerIp = /*"128.39.140.52";*/sf::IpAddress::getLocalAddress(); // remove hardcoded IP
		fprintf(configFile,"peerIp %u\n", confSettings.peerIp.toInteger());

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
			fscanf(configFile, "%255s %9d\n", variableBuffer, &valueBuffer);
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
			else if (!strcmp(variableBuffer, "isHost"))
			{
				confSettings.isHost = valueBuffer;
			}
			else if (!strcmp(variableBuffer, "chatOn"))
			{
				confSettings.chatOn = valueBuffer;
			}
			else if (!strcmp(variableBuffer, "peerIp"))
			{
				unsigned int castUInt32Addr = valueBuffer;
				confSettings.peerIp = sf::IpAddress(castUInt32Addr);
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
		fprintf(stdout,"main(int,char**): isHost %d\n", confSettings.isHost);
		fprintf(stdout,"main(int,char**): chatOn %d\n", confSettings.chatOn);
		fprintf(stdout,"main(int,char**): peerIp %s\n", confSettings.peerIp.toString().c_str());
	}

	pthread_t networkHostThread;
	pthread_t networkClientThread;
//	if (confSettings.isHost)	//comment out if
	{
		// host code, spawn thread.
		pthread_create(&networkHostThread, NULL, &chatserver, NULL);
	}
//	else				//comment out else
	{
		std::string tempString = confSettings.peerIp.toString();
		char * tempCharArray = new char [tempString.length()+1];
		strcpy (tempCharArray, tempString.c_str());
			void *tempVoidPointer = (void*) tempCharArray;
		// client code, spawn thread.
		pthread_create(&networkClientThread, NULL, &chatclient, tempVoidPointer);
	}
	pthread_join(networkHostThread, NULL);
	pthread_join(networkClientThread, NULL);
	/*
	 * We exit the program here for testing purposes during this
	 * early testing of networking.
	 */
	return 0;

	/**
	 * @todo make mapsizes parsed from arguments.
	 * @todo make System.{c,h}pp (maybe call it init?)
	 * @todo clean up int main(int,char**), move things where they
	 * 	should be(this depends of course on that the rest of
	 * 	the system is ready).
	 */

	// Open window with configured resolution
	sf::RenderWindow screen;
	sf::Music music;
	if (confSettings.fullscreen)
	{
		screen.create(sf::VideoMode(confSettings.screenwidth, confSettings.screenheight,32),
			"Neuton presents: Frank Darkhawks Maze RPG!", sf::Style::Fullscreen);
	}
	else
	{
		screen.create(sf::VideoMode(confSettings.screenwidth, confSettings.screenheight,32),
			"Neuton presents: Frank Darkhawks Maze RPG!");
	}
	screen.setFramerateLimit(20);
	//printf("main(int,char**): Before getting singletons {World, MineFactory, CharacterFactory}\n");

/*	Menu* mainMenu = new Menu(&screen);
	mainMenu->runMenu(); //*/

	World *world;
	world = world->getWorld();
	world->setWindow(&screen);
	world->runMenu();

	// Open music from an audio file
/*	if (!music.openFromFile("music/Circuit_Soldiers-Intellectual_Property_is_a_Dying_Whore.ogg"))
	{
		printf("main(int argc, char **argv): Can't load music");
	}
	else
	{
		music.setVolume(50);         // reduce the volume
		music.setLoop(true);         // make it loop
		music.play();
	}
//*/
	//printf("main(int,char**): Has got all singletons and player1\nmain(int,char**): Starting gameloop\n");
	while (screen.isOpen())
	{
		world->update();
		screen.clear();
		world->draw(&screen);
		//player1->draw(&screen);
		screen.display();

		/**
		 * @todo Fix this ugly way of checking for escape++
		 */
		// Process events
//		sf::Event event;

//		while (screen.pollEvent(event))
//		{

			//player1->characterInput(event);

			// Close window : exit
/*			if (event.type == sf::Event::Closed)
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				if(event.KeyReleased && event.key.code == sf::Keyboard::Add)
				{
					world->addDifficulty(1);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			{
				if(event.KeyReleased && event.key.code == sf::Keyboard::Subtract
					)
				{
					world->addDifficulty(-1);
				}
			} //*/
//		}
	}
	return EXIT_SUCCESS;
}
