/*
 * Network.cpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas@gmail.com>
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


Network::Network(void *params)
{
	peerIp.reserve(4);
	peerIp.assign(1, (char *) params);
	
	pthread_t networkReceiverThread;
	pthread_t networkSenderThread;

	pthread_create(&networkReceiverThread, NULL, &chatReceiver, reinterpret_cast<void *> (this));
	pthread_create(&networkSenderThread, NULL, &chatSender, reinterpret_cast<void *> (this));
	
	pthread_join(networkReceiverThread, NULL);
	pthread_join(networkSenderThread, NULL);
	
}

void *Network::chatReceiver(void *sentSelf)
{
	Network *myself = reinterpret_cast<Network*>(sentSelf);
	
	std::size_t received;
	sf::IpAddress sender;
	unsigned short port;
	sf::UdpSocket inSocket;
	inSocket.bind(4444);
	char inBuffer[1024];
	unsigned long count =0; 
	//World *world;
	//world->getWorld();
	
	

	while(true)
	{
		if (inSocket.Done == inSocket.receive(inBuffer, sizeof(inBuffer), received, sender, port)) 
		{
			count++;
			printf("%s said: %s, count: %lu\n", sender.toString().c_str(), inBuffer+1, count);
			if (!inList((char *)sender.toString().c_str()))
			{
				peerIp.assign(1, (char *)sender.toString().c_str());
			}
		}
	}
	return NULL;
}

void *Network::chatSender(void *sentSelf) //rename to sender
{
	Network *myself = reinterpret_cast<Network*>(sentSelf);
	World *world;
	world->getWorld();
	sf::UdpSocket outSocket;
	//char *outBuffer;
	//unsigned short outPort;
	outSocket.bind(4445);

	while (true)
	{
		std::string message = world->staticMapString(); //"Hi, I am " + sf::IpAddress::getLocalAddress().toString(); 
		std::vector<char *>::iterator peerIter;
		for (peerIter=peerIp.begin(); peerIter < peerIp.end(); peerIter++ )
		{
			outSocket.send(message.c_str(), message.size() + 1, *peerIter, 4444);	
		}
	}
	return NULL;
}

bool Network::inList(char *ip)
{
	std::vector<char *>::iterator peerIter;
	for (peerIter=peerIp.begin(); peerIter < peerIp.end(); peerIter++ )
	{
		if (ip == *peerIter)
		{
			return true;
		}
	}
	return false;
}