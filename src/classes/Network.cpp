/*
 * Network.cpp
 *
 * Copyright 2012, 2013 Thomas Sigurdsen <thomas@gmail.com>
 * Copyright 2013 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
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
 *
 */
#include "../Includes.hpp"

std::vector<Network::Client*> *Network::clients = NULL;
//pthread_mutex_t Network::mutexSendLock = PTHREAD_MUTEX_INITIALIZER;

Network::Network(void *params, bool isHost)// : mutexSendLock(PTHREAD_MUTEX_INITIALIZER)
{

	clients = new std::vector<Network::Client*>;
	clients->reserve(4);
	hostIp = NULL;
	if (params)
	{
		hostIp = (char *) params;
	}

	world = world->getWorld();
	world->initNetwork();

	pthread_mutex_init(&mutexSendLock, NULL);
//	pthread_cond_init(networkCV, NULL);
	networkCV = PTHREAD_COND_INITIALIZER;

	pthread_create(&networkReceiverThread, NULL, &threadInitialize, reinterpret_cast<void *> (this));
	pthread_create(&networkSenderThread, NULL, &threadInitialize, reinterpret_cast<void *> (this));

	pthread_join(networkReceiverThread, NULL);
	pthread_join(networkSenderThread, NULL);

}

void *Network::threadInitialize(void *sentSelf)
{
	Network *myself = reinterpret_cast<Network*>(sentSelf);
	if (pthread_equal(pthread_self(), myself->networkReceiverThread))
	{
		myself->chatReceiver(myself);
	}
	else if (pthread_equal(pthread_self(), myself->networkSenderThread))
	{
		myself->chatSender(myself);
	}
	else
	{
		/*	PORTABILITY WARNING
		 * pthread_t on linux(at least on my box) is a typedef
		 * of unsigned long int. This means the printf in this
		 * section may not compile or have errors on other
		 * platforms. If this is the case, uncomment the ifdef's
		 */
		//#ifdef __linux__
		printf("NetworkClient::networkInitialize(void*): Thread"
		" ID '%lu' not recognized.\n", pthread_self());
		//#endif
	}
	return NULL;
}

void *Network::chatReceiver(Network *sentSelf)
{

	std::size_t received;
	sf::IpAddress sender;
	unsigned short port;
	sf::UdpSocket inSocket;
	inSocket.bind(4444);
	char inBuffer[1024];
	unsigned long count =0;
	std::string mapString;
	std::string mapSize;
	world->getWorld();
	std::vector<Client *>::iterator peerIter;



	while(true)
	{
		if (inSocket.Done == inSocket.receive(inBuffer, sizeof(inBuffer), received, sender, port))
		{
			count++;
			if (hostIp != NULL)
			{
				int num = atoi(strtok(inBuffer, " "));
				printf("num: %d",num);
				switch (num)
				{
				case Network::ClientState::CLIENT_READY:
					break;
				case Network::ClientState::CLIENT_CONNECTING:
					if (!inList((char *)sender.toString().c_str()))
					{

						Client *tempclient = new Client;
						tempclient->peerIp = (char*) malloc(sizeof(char)*256);
						printf("\npeerip: %s\n",(char *) sender.toString().c_str());
						memcpy(tempclient->peerIp, (sender.toString().c_str()), sender.toString().size());
						tempclient->peerState = Network::ClientState::CLIENT_CONNECTING;
						printf("\n\t\tTMPCLIENT:\n\tip: %s\n\tstate: %d",tempclient->peerIp, tempclient->peerState);
						clients->push_back(tempclient);
					}
					break;
				case Network::PacketTypes::CHAT_MESSAGE:
					printf("%s said: %s, count: %lu\n", sender.toString().c_str(), inBuffer, count);
					if (clients != NULL)
					{
						for (peerIter=clients->begin(); peerIter < clients->end(); peerIter++ )
						{
							if ((*peerIter)->peerIp == (char*) sender.toString().c_str())
							{
								(*peerIter)->peerState = Network::ClientState::CLIENT_READY;
							}

						}
					}
					break;

				case Network::ClientState::CLIENT_ORDER:
					//make function to assign orders to a network player.
					break;
				default:
					printf ("WHAT THE FUCK I'M HOST: %s \n", inBuffer);
					break;
				}
			}

			else
			{
				int num = atoi(strtok(inBuffer, " "));

					switch (num)
					{
					case Network::PacketTypes::HOST_READY:
						break;

					case Network::PacketTypes::CHAT_MESSAGE:
						printf("%s said: %s, count: %lu\r", sender.toString().c_str(), inBuffer, count);
						break;

					case Network::PacketTypes::HOST_MAP:
						mapSize = strtok (NULL," ");
						mapString = strtok(NULL, " ");
						world->buildFromString(mapSize, mapString);
						break;

					case Network::PacketTypes::HOST_PLAYING: //this is where the game receives prompt to leave the chat and start the game
						break;

					case Network::PacketTypes::HOST_NUMBER_OF_PLAYERS: //this is where the game receives the number of players in game
						break;

					case Network::PacketTypes::HOST_PLAYER_POSITION: // this is where the game receives the player and which player number it is
						break;

					case Network::PacketTypes::HOST_MINE_POSITION: // this is where the game receives the mines and which mine number it is
						break;

					default:
						printf ("WHAT THE FUCK, I'M A CLIENT: %s", inBuffer);
						break;
					}

				}

			}
		}
	return NULL;
}

void *Network::chatSender(Network *sentSelf) //rename to sender
{
	World *world;
	world->getWorld();
	sf::UdpSocket outSocket;
	char *outBuffer;
	//unsigned short outPort;
	outSocket.bind(4445);
	pthread_mutex_lock(&mutexSendLock);
	while (true)
	{
		std::string message;
		std::getline(std::cin, message);
		if (message.size() > 0)
		{
			if (!hostIp)
			{
				if (clients != NULL)
				{
					std::vector<Client *>::iterator peerIter;
					for (peerIter=clients->begin(); peerIter < clients->end(); peerIter++ )
					{
						if ((*peerIter)->peerState == Network::ClientState::CLIENT_CONNECTING)
						{
							message += Network::PacketTypes::HOST_MAP + " ";
							message += world->staticMapString();
							outSocket.send(message.c_str(), message.size() + 1, (*peerIter)->peerIp, 4444);
						}
						outSocket.send(message.c_str(), message.size() + 1, (*peerIter)->peerIp, 4444);
					}
				}
			}
			else
			{
				outSocket.send(message.c_str(), message.size() + 1, hostIp, 4444);
			}
		}
	}
	/* Unlock */
	pthread_mutex_unlock(&mutexSendLock);
	return NULL;
}

bool Network::inList(char *ip)
{
	if (clients != NULL)
	{
		std::vector<Client*>::iterator peerIter;
		for (peerIter=clients->begin(); peerIter < clients->end(); peerIter++ )
		{
			if (ip == (*peerIter)->peerIp)
			{
				return true;
			}
		}
	}
	return false;
}
