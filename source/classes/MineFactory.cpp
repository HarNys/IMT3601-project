/**
 * Implementation of MineFactory.hpp's code
 */
#include "../Includes.hpp"

MineFactory *MineFactory::minefactory = NULL;

MineFactory::MineFactory()
{
	/// @todo add in whatever should be here, ie.: Vector *readyMines[] and so on
};

MineFactory *MineFactory::getMineFactory()
{
	if (minefactory == NULL)
	{
		minefactory = new MineFactory();
		return minefactory;
	}
	else
	{
		return minefactory;
	}
};

void MineFactory::initMineFactory(int possibletotal)
{
	/// @todo initialize minefactory, ie.: construct vector *readymines[]
};

MineFactory::~MineFactory()
{
	/// @todo delete all members of the factory, ie.: vector *readymines[]
};
