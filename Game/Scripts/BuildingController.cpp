#include "BuildingController.h"
#include "core\GameEngine.h"
#include "Hub.h"
BuildingController::~BuildingController()
{
}

BuildingController * BuildingController::Create(GameObject * gameObject, BuildingManager * buildingManager, Hub *hub)
{
	BuildingController *bc = new BuildingController();
	bc->buildingManager = buildingManager;
	bc->hub = hub;
	gameObject->AddComponent(bc);

	return bc;
}

void BuildingController::Copy(GameObject * copyObject)
{
	BuildingController *bc = new BuildingController();
	bc->buildingManager = buildingManager;

	copyObject->AddComponent(bc);
}

void BuildingController::SetObjectToBuild(std::string structure)
{

	if (objectToBuild)
	{
		GameEngine::manager.gameObjectManager->DeregisterGameObject(objectToBuild->name);
		delete objectToBuild;
	}
	// Create our Object and insert it to the game Loop
	structureName = structure;
	objectToBuild = buildingManager->GetBuilding(structure);
	objectToBuild->transform->Scale(vec3(5.0f));
	// Sets Wheter we want to display the object on the map or not
	objectToBuild->enabled = true;
	buildMode = true;
}

void BuildingController::Start()
{
	buildMode = false;
	
}

void BuildingController::Update(double dt)
{
	if (buildMode)
	{
		int mx, my; //Mouse Position
		GameEngine::manager.inputManager.GetMousePos(mx, my);

		//Get our Snap-point
		vec3 snapPoint = colHelper.GetMouseToTerrainSnap(vec2(mx, my));
		vec2 coordinates = colHelper.GetMouseToTerrainCoordinates();

		//Place our ghost object there
		if (objectToBuild != nullptr)
		{
			objectToBuild->transform->SetPosition(snapPoint);

			objectToBuild->enabled = true;

			/*If mouse click is pressed / event build object*/
			//Instantiate our object
			if (GameEngine::manager.inputManager.GetKey("mouse0"))
			{
				if (!mouseHeld)
				{
					mouseHeld = true;
					GameObject * structure = buildingManager->GetBuilding(structureName);
					Structure *sComponent = structure->GetComponent<Structure>();
					hub->AddStructureToNetwork(StructureType::PRODUCTION, sComponent, coordinates.x, coordinates.y);
					structure->transform->SetPosition(snapPoint);
					structure->transform->Scale(vec3(5.0f));
					buildMode = false;
				}
				
				
			}
			else {
				mouseHeld = false;
			}
			if (GameEngine::manager.inputManager.GetKey("mouse1"))
			{
				buildMode = false;
			}

			//Add it to the active hub
			//easy peezy
		}	
	}
	else
	{
		if (objectToBuild != nullptr)
		{
			objectToBuild->enabled = false;
		}
	}
		
}

void BuildingController::SetBuildMode(bool mode)
{
	buildMode = mode;
}

void BuildingController::SetMouseHeld(bool state)
{
	mouseHeld = state;
}

void BuildingController::AddTempObject(GameObject * object)
{
	objectToBuild = object;
}
