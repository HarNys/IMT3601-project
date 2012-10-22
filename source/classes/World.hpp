#ifndef __WORLD__HEADER__GUARD__
#define __WORLD__HEADER__GUARD__
#include "../Includes.hpp"

/**
 * @brief world X is across, world Y is downwards
 *
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
		int area; //size from origin to one side of the map
		int border; //size of the border around the map
		MineFactory *mineFactory;

public:
		static World *getWorld();
		bool initMap(char *mapFile);
		void randomGenerate();
		bool recursiveRandomGenerate(int *currentX, int *currentY, int directionX, int directionY, std::list<Tile*> *frontier, std::list<Tile*> *visited);
		bool randomGenerateVisit(Tile *visitTile);
		bool placeCharacter(Character *character);
		bool moveCharacter(Character *character, int xPosition, int yPosition);
		bool placeMine(Character *character, Tile *tile);
		bool update();
		void draw(sf::RenderWindow *window);

};

#endif // __WORLD__HEADER__GUARD__
