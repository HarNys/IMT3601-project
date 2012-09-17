#include "../Includes.hpp"
#include <vector>

#ifndef __MINE__FACTORY__HEADER__GUARD__
#define __MINE__FACTORY__HEADER__GUARD__

/**
 * The MineFactory, creates the grand total of mines for this map setup.
 * should get instance and init in System.
 */
class MineFactory
{
private:
	// constructor
        MineFactory();
        // member variables
		static MineFactory *minefactory;
	//Vector <MineFactory> Mine (5); 
public:
	static MineFactory *getMineFactory();
	void initMineFactory(int possibletotal);
	~MineFactory();
};

#endif // __MINE__FACTORY__HEADER__GUARD__

