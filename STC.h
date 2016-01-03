/*
 * STC.h
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#ifndef STC_H_
#define STC_H_
#define access(X,Y) ((X) < (Y) ? (true) : (false))
#include "Map.h"
#include "Node.h"
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
