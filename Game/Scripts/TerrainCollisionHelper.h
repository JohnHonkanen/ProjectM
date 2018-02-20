#pragma once
#include "components\TerrainGrid.h"
#include <glm\glm.hpp>
class TerrainCollisionHelper
{
public:
	/** Get the Snapping Point of our ray on the terrain */
	glm::vec3 GetMouseToTerrainSnap(glm::vec2 mousePosition);
	/* Get Mouse Cooridnates index in last GetMouseTerrainSnap call*/
	glm::vec2 GetMouseToTerrainCoordinates();

	void SetGrid(TerrainGrid *in_grid);
private:
	/** Determines where our point of contact is */
	glm::vec3 CalcRayTerrainCollisionPoint(glm::vec2 mousePosition);
	/** Recursive method to find the point of contact with our terrain grid 
		@param position			Position of our Camera
		@param ray				Direction that our camera is facing
		@param rayDist			Maximum Distance to check
		@param recursionCount	Count we should do recursion //The higher the value the closer, more performance
	*/
	glm::vec3 BinarySearchFindPoint(vec3 position, vec3 ray, float rayDist, int recursionCount);
	vec2 coordinates;
	TerrainGrid * grid;
	const int RAYDIST = 600;
	const int RECURSION = 200;
};