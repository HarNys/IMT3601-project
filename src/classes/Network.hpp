/*
 * Network.hpp
 *
 * Copyright 2012 Thomas Sigurdsen <thomas@gmail.com>
 * Copyright 2013 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
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

class Network
{

public:
	enum ClientState
	{
		CONNECTING,
		READY,
		PLAYING
	};
	struct Client{
		char *peerIp;
		ClientState peerState;
	};
	Network();
	Network(void *params, bool isHost);
	static void *threadInitialize(void *sentSelf);
	void *chatReceiver(Network *sentSelf);
	void *chatSender(Network *sentSelf);
	static bool inList(char *ip);
	static std::vector<Client*> *clients;
private:
	char *hostIp;
	pthread_t networkReceiverThread;
	pthread_t networkSenderThread;
	pthread_mutex_t mutexSendLock;
	pthread_cond_t networkCV;
	World *world;
};
