#ifndef __CHARACTER__HEADER__GUARD__
#define __CHARACTER__HEADER__GUARD__

#include "../Includes.hpp"

/**
 * These could probably be made int's.
 * but this is a performance issue.
 */
class Character
{
private:
	//member variables
//	float characterPosX;
//	float characterPosY;
	float characterDirectionX;
	float characterDirectionY;
	static sf::Image *characterImage;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Character();
	bool initImage();
	bool initCharacter();
	void draw(sf::RenderWindow* window);
	void draw();
	void updatePosition();
	void characterInput(sf::Event e);
	void placeMine(sf::Event e);
};

#endif //__CHARACTER__HEADER__GUARD__
