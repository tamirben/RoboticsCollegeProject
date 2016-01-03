/*
 * STC.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: greatwing - mor.zusmann@gmail.com
 */

#include "STC.h"

STC::STC(Map &map, Position startPos) : map(map) {
	buildGraph();
	startNode = graph[startPos.first][startPos.second];
	std::cout << startPos.first<< ","<<startPos.second << std::endl;

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
	std::cout << node->row<< ","<<node->col << std::endl;

	node->visited = true;
	for(int i=-1 ;i<2  ; i+=2){
		if((node->col+i) < (graph[1].size()) && !(graph[node->row][node->col+i]->visited) ){
			node->neighborsInSpanningTree.push_back(graph[node->row][node->col+i]);
			DFS(graph[node->row][node->col+i] );
		}

		if((node->row+i) < (graph.size()) && !(graph[node->row+i][node->col]->visited) ){
					node->neighborsInSpanningTree.push_back(graph[node->row+i][node->col]);
					DFS(graph[node->row+i][node->col] );
		}
	
	}
	


}
void STC::buildSpanningTree(){
	startNode->visited = true;
	DFS(startNode);
	int rows = graph.size();
		int cols = graph[0].size();

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << (graph[i][j]->visited ? "*" : " ");
			}
			cout << endl;
		}
}

	
STC::~STC() {
	// TODO Auto-generated destructor stub
}

