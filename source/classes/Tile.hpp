#ifndef __TILE__HEADER__GUARD__
#define __TILE__HEADER__GUARD__

/**
 * \brief The 'World's map arrays contains a set of 'Tile' objects(or
 * 	pointers rather). Each tile currently has a bool for whether or
 * 	not it is a floor or wall tile, a pointer to a 'Mine' object,
 * 	and a pointer to a 'Character' object.
 *
 * 	The pointers to 'Mine' and 'Character' will point to either an
 * 	empty object, or be a NULL pointer.
 *
 * \todo update documentation for wether(spelling?) pointers point to
 * 	empty object or NULL
 */
class Tile
{
private:
	bool isWall; ///< \note isWall is true when 'Tile' is a wall.
	Mine *hasMine;
	Character *hasCharacter;
public:
	Tile();
	Tile(bool wall);
	bool updateMine(Mine *mine);
	bool updateCharacter(Character *character);
	~Tile();
};

#endif // __TILE__HEADER__GUARD__
