#include "../Includes.hpp"

/**
 * Default constructor for 'Tile'. Should not be called explicitly.
 */
Tile::Tile()
{
	isWall = false;
	hasMine = NULL;
	hasCharacter = NULL;
};

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
};

/**
 * @param[in] wall: the new state of this tile, whether it is a wall
 * 	or floor
 *
 * @return true on success
 *
 * @bug segfaults on isWall = wall for some reason
 */
bool Tile::setWall(bool wall)
{
	isWall = wall;
	return true;
};

/**
 * @todo check whether there already is a mine there
 *
 * @param[in] mine: the new mine, either a NULL pointer or a 'Mine'
 *
 * @return true on success
 */
bool Tile::setMine(Mine *mine)
{
	hasMine = mine;
	return true;
};

/**
 * @param[in] character: the new character, either a NULL pointer or a
 * 	'character'
 *
 * @return true on success
 */
bool Tile::setCharacter(Character *character)
{
	/// @todo animation and drawing? think this properly through.
	///	don't just wave around grand ideas.
	return false;
};

/**
* draws the map
*
* @param [in] xPos: the x position of the tile
* @param [in] yPos: the y position of the tile
*
* @ return true on success
*/
bool Tile::initSprite(int xPos, int yPos)
{
	sf::Image image;
	if (isWall)
	{
		image.loadFromFile("img/wall.gif");
	}
	else
	{
		image.loadFromFile("img/floor.gif");
	}
	tileTexture.loadFromImage(image);

	// Create a sprite
	tileSprite.setTexture(tileTexture);
	tileSprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
	tileSprite.setColor(sf::Color(255, 255, 255, 200));
	tileSprite.setPosition(15*xPos, 15*yPos);
	return true;
};



sf::Sprite Tile::getSprite()
{
	return tileSprite;
};
/**
 * @todo "getMineFactory.releaseMine(hasMine);" should do this in a way
 * 	that works
 */
Tile::~Tile()
{
	if (hasMine)
	{
		mineFactory = mineFactory->getMineFactory();
		mineFactory->releaseMine(hasMine);
	}
	if (hasCharacter)
	{
		/// @note cannot "delete hasCharacter;" here? character
		///	factory?
	}
	delete this;
};
