#include "../Includes.hpp"


///movement-functions
///checks if the key is pressed and then released
///to reset characterDirectionX/Y
/// @todo document parameter

void LocalPlayer::characterInput(sf::Event e, Character* tempchar)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		characterDirectionX = -1;
		sprite.setTextureRect(sf::IntRect(0, 51, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::A)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		characterDirectionX = 1;
		sprite.setTextureRect(sf::IntRect(0, 17, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::D)
			characterDirectionX = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		characterDirectionY = -1;
		sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::W)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		characterDirectionY = 1;
		sprite.setTextureRect(sf::IntRect(0, 34, 15, 15));

		if(e.KeyReleased && e.key.code == sf::Keyboard::S)
			characterDirectionY = 0;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if(e.KeyReleased && e.key.code == sf::Keyboard::E)
		{
			minePlaced = true;
//			std::cout<< "Character::characterInput(sf::Event e): Mine placed\n";
		}
	}

};