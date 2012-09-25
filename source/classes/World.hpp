#ifndef __WORLD__HEADER__GUARD__
#define __WORLD__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @brief world X is across, world Y is downwards
 */
class World
{
private:
        // constructor
        World();
        // member variables
        static World *world;
        Tile ***map;
        int area; //size to a side of the map

public:
        static World *getWorld();
        bool placeCharacter(Character *character);
        void draw(sf::RenderWindow *window);
};

#endif // __WORLD__HEADER__GUARD__
