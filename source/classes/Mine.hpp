#ifndef __MINE__HEADER__GUARD__
#define __MINE__HEADER__GUARD__
#include "../Includes.hpp"

class Mine
{
private:
        // member variables
        int visibilityTimer;
public:
        // constructor
        Mine();
        bool initMine(int timeShown);
        bool update(Character *character);
        bool visibilityCountDown();
};

#endif // __MINE__HEADER__GUARD__