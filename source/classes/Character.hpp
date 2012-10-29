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
	int characterHealth;	///< How much health the player have left
	static sf::Image *characterImage;
	enum type{mine,rifle};
	int controllerType;		///< 0 for localplayer, 1 for NPC, 2 for networkPlayer.
	sf::Texture texture;
	sf::Sprite sprite;
	Node *currentNode;
	Node *nextNode;

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
	void useController(Character* thischaracter);
	void resetDirection();
	void characterInput(sf::Event e);
	void updateCharacterHealth(int health);
	sf::Sprite *getSprite();
	bool updateSprite(float xPosition, float yPosition);
	void setCurrentNode(Node *newCurrentNode);
	void setNextNode(Node *newNextNode);
	bool updateSprite();
	bool placeMine();
	bool setCharacterType(int type);
};

#endif //__CHARACTER__HEADER__GUARD__
