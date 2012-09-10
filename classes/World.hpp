#ifdef __WORLD__HEADER__GUARD__
#define __WORLD__HEADER__GUARD__

/*
 * world X is across, world Y is downwards
 */ 
Class World
{
Private:
        // constructor
        World();
        // member variables
        float world[][];
Public:
        World *getWorld();
};

#endif // __WORLD__HEADER__GUARD__
