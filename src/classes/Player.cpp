#include "../Includes.hpp"

///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @param [in] (keyboard event, pointer to character to move) 

void LocalPlayer::characterInput(Character* thisCharacter)
{
	sf::Event e;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		thisCharacter->setCharacterDirectionX(-1);
		thisCharacter->updateSprite();
		
		//if(e.KeyReleased && e.key.code == sf::Keyboard::A)
		//{
		//	thisCharacter->setCharacterDirectionX(0);
		//}
			
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		thisCharacter->setCharacterDirectionX(1);
		thisCharacter->updateSprite();

		//if(e.KeyReleased && e.key.code == sf::Keyboard::D)
		//{
		//	thisCharacter->setCharacterDirectionX(0);
		//}

	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		thisCharacter->setCharacterDirectionY(-1);
		thisCharacter->updateSprite();
		
		//if(e.KeyReleased && e.key.code == sf::Keyboard::W)
		//{
		//	thisCharacter->setCharacterDirectionY(0);
		//}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		thisCharacter->setCharacterDirectionY(1);
		thisCharacter->updateSprite();

		//if(e.KeyReleased && e.key.code == sf::Keyboard::S)
		//{
		//	thisCharacter->setCharacterDirectionY(0);
		//}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		//{
		//	thisCharacter->placeMine();
		//}
	}

};