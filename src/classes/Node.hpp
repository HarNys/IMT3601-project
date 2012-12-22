/*
 * Node.hpp
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
#ifndef __NODE__HEADER__GUARD__
#define __NODE__HEADER__GUARD__
#include "../Includes.hpp"



class Node{
private:
	int xValue;
	int yValue;
	int level;
	float estimate;
	float priority;
	Node* parent;
	bool visited;
	Node* leftChild;
	Node* rightChild;
	Node* upChild;
	Node* downChild;

protected:

public:

	Node(int posx, int posy, int step, int goalXValue, int goalYValue, Node* par = NULL);
	int getXPos ();
	int getYPos ();
	float getPriority();
	int getLevel();
	void setVisit();
	void unVisit();
	bool checkVisited();
	Node* getParent();
	Node* getUpChild();
	Node* getRightChild();
	Node* getDownChild();
	Node* getLeftChild();
	bool setUpChild(Node* newChild);
	bool setRightChild(Node* newChild);
	bool setDownChild(Node* newChild);
	bool setLeftChild(Node* newChild);

	Node* findCheapestUnusedRecursively();
	bool checkTreeRecursivelyForNode(int xCoordinates, int yCoordinates);
	~Node();

};
#endif // __NODE__HEADER__GUARD__
