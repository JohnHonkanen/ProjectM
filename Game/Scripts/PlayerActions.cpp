#include "PlayerActions.h"
#include "BuildingController.h"
#include "Hub.h"
#include "core\GameEngine.h"
#include "GameManager.h"
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
	selectedTexture = "Game/Assets/Textures/building_selected.jpg";
}

void PlayerActions::Update(double dt)
{
	if (GameManager::gameManager->mouseOverHudElement) {
		return;
	}
	int mx, my; //Mouse Position
	GameEngine::manager.inputManager.GetMousePos(mx, my);

	//Get our Snap-point
	vec3 snapPoint = buldingController->colHelper.GetMouseToTerrainSnap(vec2(mx, my));
	vec2 coordinates = buldingController->colHelper.GetMouseToTerrainCoordinates();

	//Player is not building objects
	if (!buldingController->GetBuildMode())
	{
		if (GameEngine::manager.inputManager.GetKey("mouse0"))
		{
			//Selected a building
			Structure *structure = hub->GetStructure(coordinates.x, coordinates.y);
			
			if (structure != nullptr)
			{
				if (structure->GetType() == UNBUILDABLEZONE)
				{
					return;
				}

				if (selectedStructure != nullptr)
				{
					selectedStructure->gameObject->material->diffuseMap = buildingTexture;
				}
				buildingTexture = structure->gameObject->material->diffuseMap;
				//structure->gameObject->material->diffuseMap = selectedTexture;
				selectedStructure = structure;
			}
		}
	}
	//Deselect Buildings
	if (GameEngine::manager.inputManager.GetKey("mouse1"))
	{
		if (selectedStructure != nullptr)
		{
			selectedStructure->gameObject->material->diffuseMap = buildingTexture;
		}

		selectedStructure = nullptr;
	}
}

Structure * PlayerActions::GetSelectedStructure()
{
	return selectedStructure;
}
