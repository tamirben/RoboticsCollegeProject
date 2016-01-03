/*
 * STC.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: colman
 */

#include "STC.h"

STC::STC(Map &map, Position startPos) : map(map) {
buildGraph();
startNode = graph[startPos.first][startPos.second];
}
void STC::buildGraph(){
// The graph is at the same size as the node map
	graph.resize(this->map.getNodeMap().size());
	for (int i = 0; i < graph.size(); i++) {
		graph[i].resize(map.getNodeMap()[i].size());
		for(int j=0 ; j < graph[i].size() ; j++){
			graph[i][j] = new Node(i,j);
			if(map.getNodeMap()[i][j])
				graph[i][j]->visited = true;		
		}
		
	}

}
//Recursive implementation of DFS
void STC:: DFS(Node *node)
{
//if(node->visited != true)
//
	node->visited = true;
	for(int i=-1 ;i<2  ; i+=2){
		if(access(node->col+i,graph[1].size)&& !graph[node->row][node->col+i]->visited )	
			node->neighborsInSpanningTree.push_back(graph[node->row][node->col+i]);
			DFS(graph[node->row][node->col+i] );


	
	}
	for(int i=-1 ; i <2  ; i+=2){
		if(access(node->row+i,graph.size)&& !graph[node->row+i][node->col]->visited )	
			node->neighborsInSpanningTree.push_back(graph[node->row+i][node->col]);
			DFS(graph[node->row+i][node->col] );

	}	
}
void STC::buildSpanningTree(){
DFS(startNode);
}

	
STC::~STC() {
	// TODO Auto-generated destructor stub
}

