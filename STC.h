/*
 * STC.h
 *
 *  Created on: Jan 1, 2016
 *      Author: greatwing - mor.zusmann@gmail.com
 */



#ifndef STC_H_
#define STC_H_
#define access(X,Y) X < Y ? 1 : 0
#include "Map.h"
#include "Node.h"
#include <c++/4.8.4/iostream>
using namespace std;

typedef pair<int, int> Position; //The Position will have to be the 
//Node Position (Node Coordinates and not pixels)

class STC {
private:
	Map &map;
	vector<vector< Node *> > graph;
	Node *startNode;
// each node is 24*24 pixels - in order to move from 
// one node is 24 pixels.
	void buildGraph();
	void DFS(Node *node);
public:
	STC(Map &map, Position startPos);
	void buildSpanningTree();
	virtual ~STC();
};

#endif /* STC_H_ */
