#include "TerrainCollisionHelper.h"
#include "components\Camera.h"
#include "physics\RaycastUtility.h"

glm::vec3 TerrainCollisionHelper::GetMouseToTerrainSnap(glm::vec2 mousePosition)
{
	vec3 colPoint = CalcRayTerrainCollisionPoint(mousePosition);
	coordinates = grid->GetCoordinates(colPoint);
	//Note this might have to change
	return grid->GetSnapPoint(colPoint) + vec3(5, 4.0f, 5); //Place our Object in the center of the grid
}

glm::vec2 TerrainCollisionHelper::GetMouseToTerrainCoordinates()
{
	return coordinates;
}

void TerrainCollisionHelper::SetGrid(TerrainGrid * in_grid)
{
	grid = in_grid;
}

glm::vec3 TerrainCollisionHelper::CalcRayTerrainCollisionPoint(glm::vec2 mousePosition)
{
	/** Calculate our Raycast ray */
	vec3 normCoords = RaycastUtility::ConvertPointToNormalizeCoords(mousePosition.x, mousePosition.y, 1280, 720);
	vec3 rayDir = RaycastUtility::ConvertNormalizedCoordsToWorldCoords(
		normCoords,
		Camera::mainCamera->GetProjectionMatrix(),
		Camera::mainCamera->GetViewMatrix()
	);

	/** Do a Binary Search to determine point of collision */
	return BinarySearchFindPoint(
		Camera::mainCamera->transform->GetPosition(),
		rayDir,
		RAYDIST,
		0
	);

}

glm::vec3 TerrainCollisionHelper::BinarySearchFindPoint(vec3 position, vec3 ray, float rayDist, int recursionCount)
{
	int count = recursionCount + 1;
	vec3 midPoint = position + ray * rayDist / 2.0f;

	//If we have looped greater that recursion count exit
	if (recursionCount > RECURSION)
		return midPoint;

	float tHeight = grid->GetHeight(midPoint.x, midPoint.z);


	if (midPoint.y > tHeight) {
		//Ray is Above terrain
		midPoint = BinarySearchFindPoint(midPoint, ray, rayDist / 2, count);
	}
	else if (midPoint.y < tHeight) {
		//Ray is below
		midPoint = BinarySearchFindPoint(position, ray, rayDist / 2, count);
	}

	return midPoint;
}
