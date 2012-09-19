/**
 * Default constructor for 'Tile'. Should not be called explicitly.
 */
Tile::Tile()
{
	isWall = false;
	hasMine = NULL;
	hasCharacter = NULL;
};

/**
 * @param[in] wall: the new state of this tile, whether it is a wall
 * 	or floor
 */
bool Tile::setWall(bool wall)
{
	isWall = wall;
};

/**
 * @param[in] mine: the new mine, either a NULL pointer or a 'Mine'
 */
bool Tile::setMine(Mine *mine)
{
	hasMine = mine;
};

/**
 * @param[in] character: the new character, either a NULL pointer or a
 * 	'character'
 */
bool Tile::setCharacter(Character *character)
{
	/// @todo animation and drawing? think this properly through.
	///	don't just wave around grand ideas.
};

Tile::~Tile()
{
	if (hasMine)
	{
		getMineFactory.releaseMine(hasMine);
	}
	if (hasCharacter)
	{
		/// @note cannot "delete hasCharacter;" here? character
		///	factory?
	}
	delete this;
};
