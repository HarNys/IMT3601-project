/**
 * Implementation of the mine class's functions
 */
#include "../Includes.hpp"

/**
 * Currently does nothing, we may want to make walking on a mine trigger
 * a function, rather than just damage?
 */
Mine::Mine()
{
	visibilityTimer = 0;
};

/**
 * called when a mine is placed, initializes variables as needed.
 * @param [in] timeShown: the ticks the mine is shown after being planted.
 *
 * @return true on success
 *
 * @todo when we get more Mine types; make this work on a type by type basis
 */
bool Mine::initMine(int timeShown)
{
	visibilityTimer = timeShown;
	return true;
};

/**
 * this is run every for every mine on the map.
 *
 * @param [in] Character: the character pointer on the same tile as the mine.
 *
 * @return true on success
 */
bool Mine::update(Character *character)
{
	visibilityTimer--;
	if (character)
	{
		printf("Mine::update(Character*): BANG! someone triggered a mine");
	}
	return true;
};
