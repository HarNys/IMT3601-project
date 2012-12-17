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
NetworkClient::NetworkClient()
{
	// TODO					!!!!!!
}

/**
 *
 * name: NetworkClient::networkInitialize
 * @return NULL (not used)
 */
void *NetworkClient::networkInitialize()
{
	return (void*)NULL;
}

int NetworkClient::listener()
{
	return 0;
}

int NetworkClient::sender()
{
	return 0;
}
