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
	this->empimg = new vector<unsigned char> (image);
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
	if (((i - 1) != NULL) && ((j - 1) < mapWidth) && ((i + 1) != NULL) && (((j
			+ 1)) < mapWidth))
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
void Map::buildFineGrid() {
	cout << "map size: " << mapWidth << "," << mapHeight << endl;

	fineGrid.resize(mapHeight);
	for (int i = 0; i < mapHeight; i++)
		fineGrid[i].resize(mapWidth);

	for (int i = 0; i < mapHeight; i++) {
		for (int j = 0; j < mapWidth; j++) {
			fineGrid[i][j] = checkIfCellIsOccupied(i, j, *empimg);
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

