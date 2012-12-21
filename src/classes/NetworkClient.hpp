/*
 * NetworkClient.hpp
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
 * NetworkClient class, follows the singleton pattern.
 *
 * @todo Refactor this class so it is not a singleton. Right now it is
 * 	a singleton for all the wrong reasons.
 */
class NetworkClient //: public Network
{
private:
	sf::IpAddress hostIp;
	int hostSocket;
	int mySocket;
	pthread_t listenThread;
	pthread_t sendThread;
	LocalPlayer *localPlayer;
	enum {
		MINEPLACED = 1,
		MOVEPOSITIVEX,
		MOVENEGATIVEX,
		MOVEPOSITIVEY,
		MOVENEGATIVEY,
	} playerActions;
	// constructors
	NetworkClient();
	NetworkClient(short byte0, short byte1, short byte2,
		short byte3, int hostPort, int myPort);
	static NetworkClient *networkClient;
public:
	static NetworkClient *getNetworkClient();
	int setLocalPlayer(LocalPlayer *player);
	static void *networkInitialize(void*);
	int listener();
	int sender();
};
