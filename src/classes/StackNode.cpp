/*
 * StackNode.cpp
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
#include "../Includes.hpp"



/**
 * @todo Document function
 */
StackNode::StackNode (int xPosition, int yPosition, StackNode * nextNode)
{
	positionX = xPosition;
	positionY = yPosition;
	next = nextNode;
}

/**
 * @todo Document function
 */
StackNode::StackNode ()
{
    positionX = 0;
	positionY = 0;
	next = NULL;
}

/**
 * @bug this.
 */
StackNode::~StackNode()
{

}


/**
 * @todo Document function
 */
int StackNode::getXPos()
{
	return positionX;
}

/**
 * @todo Document function
 */
int StackNode::getYPos()
{
	return positionY;
}

/**
 * @todo Document function
 */
StackNode * StackNode::getNext()
{
	return next;
}

/**
 * @todo Document function
 */
void StackNode::removeStack()
{
	if (next)
	{
		next->removeStack();
	}
	delete this;
}
