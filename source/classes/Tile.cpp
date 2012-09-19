/**
 *
 */
Tile::Tile()
{
	isWall = false;
	hasMine = NULL;
	hasCharacter = NULL;
};

Tile::Tile(bool wall)
{
};

bool Tile::updateMine(Mine *mine)
{
};

bool Tile::updateCharacter(Character *character)
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
