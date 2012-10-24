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
		enum RandomInsertion{"1234" = 1, "1243", "1423", "4123", "1324", "3124", "2134",
							 "2341", "2143" ,"3412", "3421", "3142", "4132", "4213", "4231"
							 "4321", "4312", "2413", "2431"};
		//enumerator for the procedural generation of the maze
		int currentX;
		int currentY;
		
public:


public:
		static World *getWorld();
		bool initMap(char *mapFile);
		void randomGenerate();
		bool placeCharacter(Character *character);
		bool moveCharacter(Character *character, int xPosition, int yPosition);
		bool placeMine(Character *character, Tile *tile);
		bool update();
		void draw(sf::RenderWindow *window);

};

#endif // __WORLD__HEADER__GUARD__
