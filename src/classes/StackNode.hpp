/*
 * StackNode.hpp
 *
 * Copyright 2012 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
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
#ifndef __QUEUENODE__HEADER__GUARD__
#define __QUEUENODE__HEADER__GUARD__
#include "../Includes.hpp"

/** This class is going to be a stack to character

*/

class StackNode
{
private:
	StackNode * next;
	int positionX;
	int positionY;
protected:
public:
	StackNode (int xPositon, int yPosition, StackNode * nextNode = NULL);
	StackNode ();
	~StackNode();
	void removeStack();
	StackNode* getNext();
	int getXPos();
	int getYPos();

};

#endif //__QUEUENODE__HEADER__GUARD__
