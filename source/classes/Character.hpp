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
	bool minePlaced;
	float characterDirectionX;
	float characterDirectionY;
	static sf::Image *characterImage;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Character();
	bool initImage();
	bool initCharacter();
	bool getMinePlaced();
	void setMinePlaced(bool placeMine);
	float getCharacterDirectionX();
	float getCharacterDirectionY();
	void draw(sf::RenderWindow* window);
	void updatePosition();
	void resetDirection();
	void characterInput(sf::Event e);
	void placeMine(sf::Event e);
	sf::Sprite *getSprite();
};

#endif //__CHARACTER__HEADER__GUARD__
