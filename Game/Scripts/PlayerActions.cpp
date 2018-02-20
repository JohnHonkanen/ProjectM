#include "PlayerActions.h"
#include "BuildingController.h"
#include "Hub.h"
#include "core\GameEngine.h"
PlayerActions * PlayerActions::Create(GameObject * gameObject, BuildingController * bController, Hub * hub)
{
	PlayerActions * p = new PlayerActions();
	p->buldingController = bController;
	p->hub = hub;
	gameObject->AddComponent(p);
	return p;
}

void PlayerActions::Copy(GameObject * copyObject)
{
}

void PlayerActions::Start()
{
}

void PlayerActions::Update(double dt)
{
	//Player is not building objects
	if (!buldingController->GetBuildMode())
	{
		int mx, my; //Mouse Position
		GameEngine::manager.inputManager.GetMousePos(mx, my);

		//Get our Snap-point
		vec3 snapPoint = buldingController->colHelper.GetMouseToTerrainSnap(vec2(mx, my));
		vec2 coordinates = buldingController->colHelper.GetMouseToTerrainCoordinates();

		if (GameEngine::manager.inputManager.GetKey("mouse0"))
		{
			//Selected a building
			Structure *structure = hub->GetStructure(coordinates.x, coordinates.y);
			if (structure != nullptr)
			{
				printf("Selected a building: %s \n", structure->GetName().c_str());
			}
		}
	}
}
