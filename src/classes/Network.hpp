/*
 * Network.hpp
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

class Network
{
private:
	static std::vector<char *> *peerIp;
	char *hostIp;
	pthread_t networkReceiverThread;
	pthread_t networkSenderThread;
	pthread_mutex_t mutexSendLock;
	pthread_cond_t networkCV;

public:
	Network();
	Network(void *params, bool isHost);
	static void *threadInitialize(void *sentSelf);
	void *chatReceiver(Network *sentSelf);
	void *chatSender(Network *sentSelf);
	static bool inList(char *ip);
};
