#ifndef __TILE__HEADER__GUARD__
#define __TILE__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @par
 * 	The 'World's map arrays contains a set of 'Tile' objects(or
 * 	pointers rather). Each tile currently has a bool for whether or
 * 	not it is a floor or wall tile, a pointer to a 'Mine' object,
 * 	and a pointer to a 'Character' object.
 * @par
 * 	The pointers to 'Mine' and 'Character' will be a NULL pointer.
 */
class Tile
{
private:
	bool isWall; ///< @note isWall is true when 'Tile' is a wall.
	bool visited; ///< @note visited is used for procedural generation'
	bool partOfFrontier;
	Mine *hasMine;
	Character *hasCharacter;
	MineFactory *mineFactory;
	static sf::Image *wallImg;
	static sf::Image *floorImg;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	int positionX;
	int positionY;

public:
	Tile();
	Tile(char quality);
	void setVisited(bool wall, int xPos, int yPos);
	void setFrontier();
	bool checkXY(int currentX, int currentY);
	bool getVisited();
	bool getFrontier();
	bool setWall(bool wall);
	bool setMine(Mine *mine);
	bool setCharacter(Character *character);
	bool getIsWall();
	Mine *getHasMine();
	Character *getHasCharacter();
	bool initSprite(int xPos, int yPos);
	void initImage();
	bool initTile(char quality);
	void setPosition(int xPos, int yPos);
	void setFloor(bool mineVisible);
	int returnXpos();
	int returnYpos();
	~Tile();
	sf::Sprite getSprite();
};

#endif // __TILE__HEADER__GUARD__
