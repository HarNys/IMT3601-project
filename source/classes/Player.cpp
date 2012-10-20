#include "../Includes.hpp"

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] (keyboard event, pointer to character to move) 

void LocalPlayer::characterInput(sf::Event e, Character* tempchar)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		tempchar->move('X', -1 ,0, 51, 15, 15);
		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			tempchar->move('X',0 ,0, 51, 15, 15);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		tempchar->move('X', 1 , 0, 17, 15, 15);

		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			tempchar->move('X', 0 , 0, 17, 15, 15);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		tempchar->move('Y', -1 , 0, 0, 15, 15);
		
		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			tempchar->move('Y', 0 , 0, 0, 15, 15);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		tempchar->move('Y', 1 , 0, 34, 15, 15);

		if(e.KeyReleased && e.key.code == sf::Keyboard::S)
			tempchar->move('Y', 0 , 0, 34, 15, 15);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		{
			//minePlaced = true;
//			std::cout<< "Character::characterInput(sf::Event e): Mine placed\n";
		}
	}

};