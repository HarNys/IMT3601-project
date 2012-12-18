/*
 * NetworkClient.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thoams.sigurdsen@gmail.com>
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
NetworkClient::NetworkClient(sf::Uint8 byte0,
	sf::Uint8 byte1, sf::Uint8 byte2,
	sf::Uint8 byte3, int hostPort, int myPort)
{
//	NetworkClient::NetworkClient();
	hostIp = sf::IpAddress(byte0, byte1, byte2, byte3);
	hostSocket = hostPort;
	mySocket = myPort;
	if (pthread_create(&networkThread, NULL, NetworkClient::networkInitialize, (void *)this))
	{
		printf("NetworkClient::NetworkClient([4]xUint8,int,int): "
			"pthread_create failed\n");
		exit(1);
	}

}

/**
 *
 * name: NetworkClient::networkInitialize
 * @return NULL (not used)
 */
void *NetworkClient::networkInitialize(void *lol)
{
	return NULL;
}

int NetworkClient::listener()
{
	return 0;
}

int NetworkClient::sender()
{
	return 0;
}
