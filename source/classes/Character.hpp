#ifndef __CHARACTER__HEADER__GUARD__
#define __CHARACTER__HEADER__GUARD__

#include "../Includes.hpp"

class Character
{
private:
	//member variables
	float characterPosX;
	float characterPosY;
	float characterDirectionX;
	float characterDirectionY;
	sf::Texture texture;
	sf::Sprite sprite;
//protected:

public:

	Character();
	void draw(sf::RenderWindow* window);
	void draw();
	void updatePosition();
	void characterInput(sf::Event e);
	void placeMine(sf::Event e);
};

#endif //__CHARACTER__HEADER__GUARD__
