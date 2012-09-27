#ifndef __MINE__HEADER__GUARD__
#define __MINE__HEADER__GUARD__

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
};

#endif // __MINE__HEADER__GUARD__
