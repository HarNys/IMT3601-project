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

std::vector<char *> *Network::peerIp = NULL;
//pthread_mutex_t Network::mutexSendLock = PTHREAD_MUTEX_INITIALIZER;

Network::Network(void *params)// : mutexSendLock(PTHREAD_MUTEX_INITIALIZER)
{
	peerIp = new std::vector<char *>();
	peerIp->reserve(4);
	peerIp->assign(1, (char *) params);

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
	//World *world;
	//world->getWorld();



	while(true)
	{
		if (inSocket.Done == inSocket.receive(inBuffer, sizeof(inBuffer), received, sender, port))
		{
			count++;
			printf("%s said: %s, count: %lu\r", sender.toString().c_str(), inBuffer+1, count);
			pthread_mutex_unlock(&mutexSendLock);
			if (!inList((char *)sender.toString().c_str()))
			{
				peerIp->assign(1, (char *)sender.toString().c_str());
			}
		}
	}
	return NULL;
}

void *Network::chatSender(Network *sentSelf) //rename to sender
{
//	Network *myself = reinterpret_cast<Network*>(sentSelf);
	World *world;
	world->getWorld();
	sf::UdpSocket outSocket;
	//char *outBuffer;
	//unsigned short outPort;
	outSocket.bind(4445);

	pthread_cond_wait(&networkCV, &mutexSendLock);
	while (true)
	{
		std::string message;
		scanf ("%s", message);//world->staticMapString(); //"Hi, I am " + sf::IpAddress::getLocalAddress().toString();
		std::vector<char *>::iterator peerIter;
		for (peerIter=peerIp->begin(); peerIter < peerIp->end(); peerIter++ )
		{
			outSocket.send(message.c_str(), message.size() + 1, *peerIter, 4444);
		}
		pthread_mutex_lock(&mutexSendLock);
	}
	return NULL;
}

bool Network::inList(char *ip)
{
	std::vector<char *>::iterator peerIter;
	for (peerIter=peerIp->begin(); peerIter < peerIp->end(); peerIter++ )
	{
		if (ip == *peerIter)
		{
			return true;
		}
	}
	return false;
}
