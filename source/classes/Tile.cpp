#include "../Includes.hpp"

sf::Image *Tile::wallImg = NULL;
sf::Image *Tile::floorImg = NULL;

/**
 * Default constructor for 'Tile'. Should not be called explicitly.
 */
Tile::Tile()
{
	isWall = false;
	hasMine = NULL;
	hasCharacter = NULL;
	characterFactory = characterFactory->getCharacterFactory();
	mineFactory = mineFactory->getMineFactory();
	printf("Tile::Tile(): done standard Tile constructor\n");
};

/**
 * Constructor for Tile, this is the one that should be used.
 *
 * @param[in] quality what type of Tile this should be initialized as.
 */
Tile::Tile(char quality)
{
	if(quality=='x')
	{
		isWall = true;
	}
	else
	{
		isWall = false;
	}
	hasMine = NULL;
	hasCharacter = NULL;
	characterFactory = characterFactory->getCharacterFactory();
	mineFactory = mineFactory->getMineFactory();
	printf("Tile::Tile(char): done overloaded Tile constructor\n");
};

/**
 * @param[in] wall: the new state of this tile, whether it is a wall
 * 	or floor
 *
 * @return true on success
 */
bool Tile::setWall(bool wall)
{
	if(wall)
	{
		isWall = true;
	}
	else
	{
		isWall = false;
	}
	return true;
};

/**
 * returns the true or false based on the isWall bool.
 *
 * @return value of the isWall bool
 */
bool Tile::getIsWall()
{
	return isWall;
};

/**
 * returns a pointer to the Mine on this tile. This Mine pointer is NULL if
 * this Tile has no mine so you need to check for this when using this method.
 *
 * @return the Mine on this Tile, NULL if no Mine is present.
 */
Mine *Tile::getHasMine()
{
	return hasMine;
};

/**
 * returns a pointer to the Character on this tile. This Character pointer is
 * NULL if this Tile has no Character you need to check for this when using
 * the method.
 *
 * @return the Character on this Tile, NULL if no Character is present.
 */
Character *Tile::getHasCharacter()
{
	return hasCharacter;
};

/**
 * sets all of a Tile's variables to sent values.
 * This is for reading in a new map, therefore hasMine and hasCharacter should
 * be NULL, as this is initialized by the world at a later time.
 *
 * @param[in] quality: the character read from the map, x is wall anything else is floor
 *
 * @return true on success
 */
bool Tile::initTile(char quality)
{
	if(quality == 'x')
	{
		isWall = true;
	}
	else
	{
		isWall = false;
	}
	hasMine = NULL;
	hasCharacter = NULL;
	return true;
};

/**
 * Sets hasMine if it is empty.
 *
 * @param[in] mine: the new mine, either a NULL pointer or a 'Mine'
 *
 * @return true on success
 */
bool Tile::setMine(Mine *mine)
{
	if (hasMine)
	{
		return false;
	}
	else
	{
		hasMine = mine;
	}
	return true;
};

/**
 * @param [in] character: the new character, either a NULL pointer or a
 * 	'character'
 *
 * @return true on success
 */
bool Tile::setCharacter(Character *character)
{
	hasCharacter = character;
	return true;
};

/**
 * Initializes the sprites used in Tiles
 *
 * @param [in] xPos: the x position of the tile
 * @param [in] yPos: the y position of the tile
 *
 * @return true on success
 *
 * @todo proper parameter names.
 */
bool Tile::initSprite(int xPos, int yPos)
{
	if (isWall)
	{
		tileTexture.loadFromImage(*wallImg);
	}
	else
	{
		tileTexture.loadFromImage(*floorImg);
	}
	// Create a sprite
	tileSprite.setTexture(tileTexture);
	tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	tileSprite.setColor(sf::Color(255, 255, 255, 200));
	tileSprite.setPosition(15*xPos, 15*yPos);
//	tileSprite.setScale(); /// @todo we need to make these two work, halfway there?
	return true;
};


/**
 * Gets the sf::Sprite for this Tile.
 *
 * @return this Tile's tileSprite.
 */
sf::Sprite Tile::getSprite()
{
	return tileSprite;
};

/**
 * loads the static images for floor and wall. should be done only once
 */
void Tile::initImage()
{
	wallImg = new sf::Image;
	floorImg = new sf::Image;
	if ((*wallImg).loadFromFile("img/wall.gif"))
	{
		printf("Tile::initImage(): loaded img/wall.gif\n");
	}
	if ((*floorImg).loadFromFile("img/floor.gif"))
	{
		printf("Tile::initImage(): loaded img/floor.gif\n");
	}
};

/**
 * sets visibility of the floor
 *
 * @param [in] mineVisible: true sets the Mine sprite; false sets floor sprite.
 */
void Tile::setFloor(bool mineVisible)
{
	if (mineVisible)
	{
		tileSprite.setTextureRect(sf::IntRect(17, 0, 16, 16));
	}
	else
	{
		tileSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
};

/**
 * Releases and sets to NULL the hasMine and hasCharacter pointer in this Tile.
 */
Tile::~Tile()
{
	if (hasMine)
	{
		mineFactory->releaseMine(hasMine);
		hasMine = NULL;
	}
	if (hasCharacter)
	{
		characterFactory->releaseCharacter(hasCharacter);
		hasCharacter = NULL;
	}
};
