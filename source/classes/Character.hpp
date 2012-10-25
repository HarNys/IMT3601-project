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
	int controllerType;		///< 0 for localplayer, 1 for NPC, 2 for networkPlayer.
	sf::Texture texture;
	sf::Sprite sprite;

public:
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
	void useController(sf::Event e, Character* thischaracter);
	void resetDirection();
	void updateCharacterHealt(int health);
	sf::Sprite *getSprite();
	bool updateSprite(float xPosition, float yPosition);
	bool Character::updateSprite();
	bool placeMine();
};

#endif //__CHARACTER__HEADER__GUARD__
