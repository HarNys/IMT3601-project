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
		MineFactory *mineFactory;
		//enumerator for the procedural generation of the maze
		int border;

public:
		static World *getWorld();
		bool initMap(char *mapFile);
		void startRandomGenerate(sf::RenderWindow *screen);
		bool randomGenerate(int currentX, int currentY, std::list<Tile*> *frontierList, sf::RenderWindow *screen);
		bool randomGenerateVisit(int xCoordinate, int yCoordinate, int hasMovedDirectionX, int hasMovedDirectionY);
		bool populateFrontier(int currentX, int currentY, std::list<Tile*> *frontier);
		sf::Vector2i* getTilePosition(Tile *sentTile);
		bool placeCharacter(Character *character);
		bool moveCharacter(Character *character, int xPosition, int yPosition);
		bool placeMine(Character *character, Tile *tile);
		bool update();
		void draw(sf::RenderWindow *window);

};

#endif // __WORLD__HEADER__GUARD__
