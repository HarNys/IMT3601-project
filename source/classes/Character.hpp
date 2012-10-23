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
	enum type{mine,rifle};
	sf::Texture texture;
	sf::Sprite sprite;

public:
	/// @todo This should really not be here!
	CharacterController* mController;
	// methods
	Character();
	bool initImage();
	bool initCharacter();
	bool getMinePlaced();
	void setMinePlaced(bool minePlace);
	int getCharacterDirectionX();
	int getCharacterDirectionY();
	bool setCharacterDirectionX(int newXDirection);
	bool setCharacterDirectionY(int newYDirection);
	void draw(sf::RenderWindow* window);
	void updatePosition(sf::Event e, Character* thischaracter);
	void resetDirection();
	void updateCharacterHealt(int health);
	void move(char CharacterDirection, int moveDirection, int drawTopCornerX, int drawTopCornerY, int drawWith, int drawHight);
	sf::Sprite *getSprite();
	bool updateSprite(float xPosition, float yPosition);
};

#endif //__CHARACTER__HEADER__GUARD__
