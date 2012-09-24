/**
 * @brief Implementation of MineFactory.hpp's code
 */
#include "../Includes.hpp"

MineFactory *MineFactory::mineFactory = NULL;

MineFactory::MineFactory()
{
	/// @todo not sure if resize(30) is correct, check.
	/// @note 30+2 is chosen because 15x15 is the default map size
	usedMines.resize(32);
	readyMines.reserve(32);

	/// @note This may be extremely ugly, or ok?
	//readyMines.assign(30, new Mine);

/// @note This is code from before i thought of using assign(),
///	if assign is ugly we may opt to go back to this.

	std::vector<Mine *>::iterator rmIter;
	Mine * tempMine;

	for (rmIter = readyMines.begin(); rmIter < readyMines.end(); rmIter++ )
	{

		tempMine = new Mine;
		*(rmIter) = tempMine;
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
 * @brief Moves the last mine from 'readyMines' to 'usedMines' before it
 * 	returns a pointer to it.
 *
 * @return pointer to a ready mine
 *
 * @todo if (readyMine.reInit()) { return pointer } else { wtf error }
 * @todo add mine-type as parameter here and to reInit()
 * @bug segfaults when placing mine 31
 */
Mine* MineFactory::getMine()
{
	std::vector<Mine *>::iterator rmIter;
//	for (rmIter = readyMines.begin(); rmIter < readyMines.end(); rmIter++ )

	int rmSize = readyMines.size();
	Mine *tempMine = NULL;
	if (rmSize >= 0)
	{
		if (usedMines.size() < 30)
		{
			tempMine = readyMines.at(rmSize-1);
			/// @todo tempMine.reInit();
			usedMines.push_back(tempMine);
			readyMines.pop_back();
		}
		else
		{
			printf("MineFactory::getMine(): readyMines is empty,"
				"wont give you anymore mines until the bug"
				"is fixed\n");
		}
	}
	else
	{
		printf("MineFactory::getMine(): There are probably no "
			"more ready mines. Two explanations are: the "
			"map is full of mines, or the program is "
			"leaking mines.\n");
	}
	return tempMine;
}

/**
 * @brief Moves a released mine from 'usedMines' to 'readyMines'.
 *
 * @param[in] releasedMine: pointer to the mine which is released.
 */
void MineFactory::releaseMine(Mine *releasedMine)
{
	readyMines.push_back(releasedMine);
	std::vector<Mine *>::iterator umIter;
	for (umIter=usedMines.begin(); umIter < usedMines.end(); umIter++ )
	{
		if ((*umIter) == releasedMine)
		{
			usedMines.erase(umIter);
			return;
		}
	}
	return;
}

/**
 * @brief Resizes the minefactory to a given size. It returns false if
 * 	'possibleTotal' is less than it was initialized to, this is by
 * 	design.
 *
 * @param[in] possibleTotal: new size total of "readymines + usedmines"
 * @return returns true on success, false on failure.
 */
bool MineFactory::resizeMineFactory(int possibleTotal)
{
	int tmpPossibleTotal = possibleTotal + 2;
	int rmMSize = readyMines.max_size();
	if (tmpPossibleTotal == rmMSize)
	{
		printf("MineFactory::resizeMineFactory(int): Did"
			"nothing, was already at requested value");
		return true;
	}
	else if (tmpPossibleTotal < rmMSize)
	{
		printf("MineFactory::resizeMineFactory(int): Cannot "
			"shrink factory");
		return false;
	}
	else if (tmpPossibleTotal > rmMSize)
	{
		/// @note We may want to do proper testing on
		///	'usedMines' also
		readyMines.resize(tmpPossibleTotal);
		usedMines.resize(tmpPossibleTotal);
		printf("MineFactory::resizeMineFactory(int): Resized "
			"factory to: %d", tmpPossibleTotal);
		return true;
	}
	printf("MineFactory::resizeMineFactory(int): Function should "
			"NEVER reach this point.\n\tpossibletotal: %d "
			"\n\ttmpPossibleTotal: %d", possibleTotal,
			tmpPossibleTotal);
	return false;
};

/**
 * @brief Deletes mines in both 'readyMines' and 'usedMines' before
 * 	deleting itself.
 * @todo do a for instead of clear
 * @bug segfaults her, maybe?
 */
MineFactory::~MineFactory()
{
	readyMines.clear();
	usedMines.clear();
	delete this;
};
