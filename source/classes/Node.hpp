#ifndef __NODE__HEADER__GUARD__
#define __NODE__HEADER__GUARD__
#include "../Includes.hpp"



class Node{
private:
	int xValue;
	int yValue;
	int level;
	float estimate;
	float priority;
	Node* parent;
	bool visited;
	
protected:

public:
	
	Node(int posx, int posy, int step, int goalXValue, int goalYValue, Node* par = NULL);
	int getXPos ();
	int getYPos ();
	float getPriority();
	int getLevel(); 
	void setVisit();
	void unVisit();
	bool checkVisited();
	Node* getParent();
	Node* leftChild;
	Node* rightChild;
	Node* upChild;
	Node* downChild;
	Node* findCheapestUnusedRecursively();
	bool checkTreeRecursivelyForNode(int xCoordinates, int yCoordinates);

};
#endif // __NODE__HEADER__GUARD__