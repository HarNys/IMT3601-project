/*
 * NonPlayerCharacter.hpp
 *
 *
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
#ifndef __NPC__HEADER__GUARD__
#define __NPC__HEADER__GUARD__
#include "../Includes.hpp"


/** this class is going to have the AI

*/
class NonPlayerCharacter
{
private:
Node * startNode;
Node * goalNode;

protected:
public:
	NonPlayerCharacter();
	void aStar(Tile*** const map, Character* thisCharacter);
	Node *addFrontier(int xCoord,int yCoord,int xDir,int yDir, Node *nodeParent, Character* movingChar);
};


#endif  //__AI__HEADER__GUARD__
