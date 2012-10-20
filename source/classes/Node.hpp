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
	
	Node();
	Node(int posx, int posy, Node* par = NULL, int step; int goalXValue, int goalYValue);
	int getXPos ();
	int getYPos ();
	float getPriority();
	int getLevel(); 
	void visit();
	Node* getParent();
	Node* findCheapestUnusedRecursively();
	Node* leftChild;
	Node* rightChild;
	Node* upChild;
	Node* downChild;
	

};
#endif  __NODE__HEADER__GUARD__