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
 * NetworkClient singleton handler.
 *
 * @return Singleton instance of NetworkClient.
 *
 * @todo look at a way of not hardcoding the ports.
 * @todo refactor the IP address reading into it's own function.
 */
static NetworkClient *NetworkClient::getNetworkClient()
{
	if (networkClient == NULL)
	{
		short ipbyte0 = 127;
		short ipbyte1 = 0;
		short ipbyte2 = 0;
		short ipbyte3 = 1;
		printf("NetworkClient::getNetworkClient(): User input:\n");
		printf("\tClient setup:\n"
			"\tPlease enter the IP address of the host.\n"
			"\tDefault and example: %d.%d.%d.%d: ",
			ipbyte0, ipbyte1, ipbyte2, ipbyte3);
		if (4 != scanf("%hd.%hd.%hd.%hd", &ipbyte0, &ipbyte1, &ipbyte2, &ipbyte3))
		{
			printf("\n\tIncorrect value entered: %d.%d.%d."
				"%d\n", ipbyte0, ipbyte1, ipbyte2, ipbyte3);
			ipbyte0 = 127;
			ipbyte1 = 0;
			ipbyte2 = 0;
			ipbyte3 = 1;
			printf("\tUsing default: %d.%d.%d.%d\n",
				ipbyte0, ipbyte1, ipbyte2, ipbyte3);
		}
		networkClient = new NetworkClient(ipbyte0, ipbyte1, ipbyte2, ipbyte3, 4444, 4444);
	}
	return networkClient;
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
	return 0;
}
