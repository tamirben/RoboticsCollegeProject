/*
 * Main.cpp
 * 31/12/2015 -
 *  1. Map.cpp - > we changed the saveMapFromFile in order to puff the map.
 *  	we used several private functions -  bounderies checker of the new map .
 *  2. empimp - new img for the puffed map picture.
 *  3. Map.cpp -> buildFineGrid - initial finegrid object from the class.
 *
 */

#include "Map.h"

int main() {
	float mapResolution = 0.025;
	float robotSize = 0.3;
	Map map(mapResolution, robotSize);

	const char *filePath = "roboticLabMap.png";
	map.loadMapFromFile(filePath);

	const char *outputFile = "newRoboticLabMap.png";
	map.saveMapToFile(outputFile);
	map.buildFineGrid();
	map.buildCoarseGrid();
	return 0;
}


