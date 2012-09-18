/**
 * @brief Implementation of MineFactory.hpp's code
 */
#include "../Includes.hpp"

MineFactory *MineFactory::mineFactory = NULL;

MineFactory::MineFactory()
{
	/// @todo not sure if resize(30) is correct, check.
	/// @note 30 is chosen because 15x15 is the default map size
	readyMines.resize(30);
	int rmSize = readyMines.size();
	for (int rmCount = 0; rmCount > rmSize; rmCount++)
	{
		readyMines[rmCount] = new Mine;
	}
};

MineFactory *MineFactory::getMineFactory()
{
	if (mineFactory == NULL)
	{
		mineFactory = new MineFactory();
		return mineFactory;
	}
	else
	{
		return mineFactory;
	}
};

/**
 * resizes the minefactory to a given size
 * @todo this may be a retarded way of using this function, change it?
 *
 * @param[in] new size total of "readymines + usedmines"
 * @return returns true on success, false on failure.
 */
bool MineFactory::initMineFactory(int possibleTotal)
{
	int rmMSize = readyMines.max_size();
	if (possibleTotal == rmMSize)
	{
		return true;
	}
	else if (possibleTotal < rmMSize)
	{
	}
	return false;
};

MineFactory::~MineFactory()
{
	/// @todo delete all members of the factory, ie.: vector *readymines[]
};
