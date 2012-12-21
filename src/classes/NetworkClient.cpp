/*
 * NetworkClient.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
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
#include "../Includes.hpp"

/**
 * name: NetworkClient::NetworkClient
 * Default constructor for the NetworkClient object.
 */
NetworkClient::NetworkClient()
{
	hostIp = NULL;
	hostSocket = 0;
	mySocket = 0;
	iAmSending = true;
}

/**
 * name: NetworkClient::NetworkClient
 * Parameterized constructor for the NetworkClient object.
 */
NetworkClient::NetworkClient(short byte0, short byte1, short byte2,
	short byte3, int hostPort, int myPort)
{
	hostIp = sf::IpAddress(byte0, byte1, byte2, byte3);
	hostSocket = hostPort;
	mySocket = myPort;
	iAmSending = true;
	if (pthread_create(&listenThread, NULL, &NetworkClient::networkInitialize, reinterpret_cast<void *> (this)))
	{
		printf("NetworkClient::NetworkClient([4]xUint8,int,int): "
			"pthread_create failed, listenThread\n");
		exit(1);
	}
	if (pthread_create(&sendThread, NULL, &NetworkClient::networkInitialize, reinterpret_cast<void *> (this)))
	{
		printf("NetworkClient::NetworkClient([4]xUint8,int,int): "
			"pthread_create failed, sendThread\n");
		exit(1);
	}
}

/**
 *
 * name: NetworkClient::networkInitialize
 *
 * @param sentSelf Pointer to this object, the NetworkClient object we
 * 	are going to be working in.
 *
 * @return NULL (not used)
 */
void *NetworkClient::networkInitialize(void *sentSelf)
{
	NetworkClient *myself = reinterpret_cast<NetworkClient*>(sentSelf);
	if (pthread_equal(pthread_self(), myself->listenThread))
	{
		myself->listener();
	}
	else if (pthread_equal(pthread_self(), myself->sendThread))
	{
		myself->sender();
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

/**
 * Listens to the host, and acts upon all messages from it.
 * Possible actions are:
 * @li Update World::map[][]
 *
 * @return 0, not used.
 *
 * @todo Implement World::updateMap and call it in an appropriate
 * 	manner.
 */
int NetworkClient::listener()
{
	if (DEBUG > 0)
	{
		printf("NetworkClient::listener(): In thread: \t%lu\n", pthread_self());
	}
	return 0;
}

/**
 * Sends all the actions of the local player, to the host.
 * @return 0, not used.
 */
int NetworkClient::sender()
{
	if (DEBUG > 0)
	{
		printf("NetworkClient::sender(): In thread: \t%lu\n", pthread_self());
	}
	while (iAmSending)
	{
		if (DEBUG > 0)
		{
			printf("NetworkClient::sender(): If I fail here"
				" it may be because I do not lock my\n"
				"NetworkClient::sender(): mutex before "
				"calling pthread_cond_wait.\n");
		}
		pthread_cond_wait(playerCharacter->getSenderCV(),
			playerCharacter->getActionMutex());
		printf("NetworkClient::sender(): I STOP HERE UNFINISHED"
			"!\n");
		iAmSending = false;
		/*
		 * The rest of this function would be something like
		 * this:
		 * # lock mutex.
		 * # copy players actionQueue.
		 * # unlock mutex.
		 * # send all items in actionQueue (this may be
		 * 	something we want to do in a separate thread.
		 * # loop back up to start.
		 */
	}
	return 0;
}

/**
 * Setter for the Character contained within NetworkClient
 * @param player The Character who is the local player for this client
 * @return 0 on success.
 */
int NetworkClient::setPlayerCharacter(Character *player)
{
	if (player->getType())
	{
		printf("NetworkClient::setPlayerCharacter(Character*): "
			"'player' is not this clients player."
			" Wrong type\n");
		return 1;
	}
	playerCharacter = player;
	return 0;
}
