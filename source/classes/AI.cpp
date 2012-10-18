#include "../Includes.hpp"

void NonePlayerCharacter::aStar(Tile**** const map)
{

}

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] pointer to character to move

void NonePlayerCharacter::movement(Character* tempchar)
{
	if(/*move x -1*/0)
	{
		tempchar->move('X', -1 ,0, 51, 15, 15);
		
	}
	else /*stop movement*/
	{
		tempchar->move('X',0 ,0, 51, 15, 15);
	}


};