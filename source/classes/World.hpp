#ifndef __WORLD__HEADER__GUARD__
#define __WORLD__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @brief world X is across, world Y is downwards
 *
 * @todo add the mine image to Tile's image list
 * @todo fix clock for timing of ticks
 */
class World
{
private:
        // constructor
        World();
        // member variables
        static World *world;
        Tile ***map;
        int area; //size from origin to a side of the map
        MineFactory *mineFactory;

public:
        static World *getWorld();
        bool placeCharacter(Character *character);
        bool placeMine(Character *character, Tile *tile);
        bool update();
        void draw(sf::RenderWindow *window);
};

#endif // __WORLD__HEADER__GUARD__
