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
	bool minePlaced; ///< whether or not we want to place a Mine.
	int characterDirectionX; ///< Changed from float to int
	int characterDirectionY; ///< Changed from float to int
	int characterHealth;	///< How much healt the player have left
	static sf::Image *characterImage;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Character();
	bool initImage();
	bool initCharacter();
	bool getMinePlaced();
	void setMinePlaced(bool minePlace);
	float getCharacterDirectionX();
	float getCharacterDirectionY();
	void draw(sf::RenderWindow* window);
	void updatePosition();
	void resetDirection();
	void characterInput(sf::Event e);
	void updateCharacterHealt(int health);
	sf::Sprite *getSprite();
};

#endif //__CHARACTER__HEADER__GUARD__
