#include "../Includes.hpp"

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] (keyboard event, pointer to character to move) 

void LocalPlayer::characterInput(sf::Event e, Character* thisCharacter)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		thisCharacter->updateSprite(-1, 0);
		thisCharacter->move('X', -1);
		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			thisCharacter->move('X', 0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		thisCharacter->updateSprite(1, 0);
		thisCharacter->move('X', 1);

		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			thisCharacter->move('X', 0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		thisCharacter->updateSprite(0, -1);
		thisCharacter->move('Y', -1);
		
		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			thisCharacter->move('Y', 0);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		thisCharacter->updateSprite(0, 1);
		thisCharacter->move('Y', 1);

		if(e.KeyReleased && e.key.code == sf::Keyboard::S)
			thisCharacter->move('Y', 0);
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