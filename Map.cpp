/*
 * Map.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: colman
 */

#include "Map.h"
#include "lodepng.h"
#include <iostream>

Map::Map(float mapResolution, float robotSize) :
		mapResolution(mapResolution), robotSize(robotSize) {

	robotSizeInCells = robotSize / mapResolution;
	inflationRadius = 0.3 * robotSizeInCells;
}

void Map::saveMapToFile(const char* filePath) {
	// Example: Color the first 10 rows of the image with red
	this->empimg = new vector<unsigned char>(image);
	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			if (checkIfCellIsOccupied(i, j, image) && boundMap(i, j, *empimg)) {

				colorCell(i, j, *empimg);
			}

		}

	}

	lodepng::encode(filePath, *empimg, mapWidth, mapHeight);
}
void Map::colorCell(int i, int j, vector<unsigned char>& image) {
	for (int k = -1; k < 2; k++) {
		for (int p = -1; p < 2; p++) {
			int c = ((i + k) * mapWidth + (j + p)) * 4;
			image[c] = 0;
			image[c + 1] = 0;
			image[c + 2] = 0;
		}
	}
}

bool Map::boundMap(int i, int j, vector<unsigned char> image) {

	int c = (i * mapWidth + j) * 4;
	if (((i - 1) != NULL) && ((j - 1) < mapWidth) && ((i + 1) != NULL)
			&& (((j + 1)) < mapWidth))
		return true;

	return false;
}

void Map::loadMapFromFile(const char* filePath) {

	lodepng::decode(image, mapWidth, mapHeight, filePath);

	cout << "map size: " << mapWidth << "," << mapHeight << endl;

	map.resize(mapHeight);
	for (int i = 0; i < mapHeight; i++)
		map[i].resize(mapWidth);

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			map[i][j] = checkIfCellIsOccupied(i, j, image);
		}
	}

	printGrid(map);
}
//Fine greed - each cell is in the side of the robot - 12*12 p
//which means that every 12*12 cell from 0,0 with a true in the 
//original grid is sequencly true in the new grid (fine grid)
void Map::buildFineGrid() {
	cout << "map size: " << mapWidth / ROBOT_SIZE << ","
			<< mapHeight / ROBOT_SIZE << endl;
	int _newMapHeight = mapHeight / ROBOT_SIZE;
	int _newMapWidth = mapWidth / ROBOT_SIZE;
	fineGrid.resize(_newMapHeight);

	for (int i = 0; i < _newMapHeight; i++)
		fineGrid[i].resize(_newMapWidth);

	for (unsigned int p = 0; p < (mapHeight-ROBOT_SIZE); p += ROBOT_SIZE) { // mapHeight-ROBOT = so that the iterations w'ont go out of
		//of border.
		for (unsigned int k = 0; k < (mapWidth-ROBOT_SIZE); k += ROBOT_SIZE) {
			bool flag = false;
			for (int i = 0; i < ROBOT_SIZE; i++) {
				for (int j = 0; j < ROBOT_SIZE; j++) {
					if (checkIfCellIsOccupied(i + p, j + k, *empimg))
						flag = true;
				}
			}

			fineGrid[p / ROBOT_SIZE][k / ROBOT_SIZE] = flag;
		}
	}

	printGrid(fineGrid);
}
bool Map::checkIfCellIsOccupied(int i, int j, vector<unsigned char>& image) {
	int c = (i * mapWidth + j) * 4;
	int r = image[c];
	int g = image[c + 1];
	int b = image[c + 2];

	if (r == 0 && g == 0 && b == 0)
		return true;
	return false;
}

void Map::printGrid(const Grid &grid) const {
	int rows = grid.size();
	int cols = grid[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << (grid[i][j] ? "*" : " ");
		}
		cout << endl;
	}
}

Map::~Map() {
	delete empimg;
}




