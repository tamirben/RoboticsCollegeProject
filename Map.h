/*
 * Map.h
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#define ROBOT_SIZE 12
#define ROBOT_SIZE_DOUBLE 24
#include <vector>
#include "Node.h"
using namespace std;

typedef vector<vector<bool> > Grid;
class Map {
private:
	vector<unsigned char> image;
	Grid map;
	
	Grid fineGrid; // each cell in the size of the robot
	Grid coarseGrid; // each cell in the size 2x2 of the fine grid cell
	
	unsigned int mapWidth;
	unsigned int mapHeight;
	vector<unsigned char> *empimg;
	float mapResolution;
	float robotSize;
	int robotSizeInCells;
	int inflationRadius;
	bool boundMap(int i , int j , vector<unsigned char> image) const;
	bool checkIfCellIsOccupied(int i, int j, vector<unsigned char >& image) const;
	void printGrid(const Grid &grid) const;
	void colorCell(int i , int j, vector<unsigned char>& image);

public:
	Map(float mapResolution, float robotSize);
	void loadMapFromFile(const char* filePath) ;
	void saveMapToFile(const char* filePath) ;


	void buildFineGrid();
	void buildCoarseGrid();

	virtual ~Map();

	const Grid& getNodeMap() const {
		return coarseGrid;
	}

	void setNodeMap(const Grid& coarseGrid) {
		this->coarseGrid = coarseGrid;
	}
};

#endif /* MAP_H_ */
