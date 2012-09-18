#ifndef __MINE__FACTORY__HEADER__GUARD__
#define __MINE__FACTORY__HEADER__GUARD__

#include "../Includes.hpp"
/**
 * @brief The MineFactory, creates the grand total of mines for this map setup.
 *
 * @todo should get instance and init in System.
 * @note later we may want to have a constructor with a size parameter.
 */
class MineFactory
{
private:
	// constructor
        MineFactory();
        // member variables
        static MineFactory *mineFactory;
	std::vector<Mine*> readyMines;
public:
	static MineFactory *getMineFactory();
	bool initMineFactory(int possibleTotal);
	~MineFactory();
};

#endif // __MINE__FACTORY__HEADER__GUARD__

