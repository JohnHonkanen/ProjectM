#include "BuildingController.h"
#include "core\GameEngine.h"

BuildingController::~BuildingController()
{
}

BuildingController * BuildingController::Create(GameObject * gameObject, BuildingManager * buildingManager)
{
	BuildingController *bc = new BuildingController();
	bc->buildingManager = buildingManager;

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
	//If already holding an object, delete it from the game loop
	if (objectToBuild != nullptr)
	{
		GameEngine::manager.gameObjectManager->DeregisterGameObject(objectToBuild->name);
		delete objectToBuild;
	}

	// Create our Object and insert it to the game Loop
	objectToBuild = buildingManager->GetBuilding(structure)->Instantiate();
	// Sets Wheter we want to display the object on the map or not
	objectToBuild->enabled = showGameObject;
}

void BuildingController::Start()
{
	showGameObject = true;
	
}

void BuildingController::Update(double dt)
{
	if (objectToBuild != nullptr)
	{
		//Set Gameobject to enabled state according to wheter we want it to show
		objectToBuild->enabled = showGameObject;
	}
	

	if (showGameObject)
	{
		int mx, my; //Mouse Position
		GameEngine::manager.inputManager.GetMousePos(mx, my);

		//Get our Snap-point
		vec3 snapPoint = colHelper.GetMouseToTerrainSnap(vec2(mx,my));

		//Place our ghost object there
		if (objectToBuild != nullptr)
		{
			objectToBuild->transform->SetPosition(snapPoint);
		}
		

		/*If mouse click is pressed / event build object*/
		//Instantiate our object
		if (GameEngine::manager.inputManager.GetKey("mouse0"))
		{
			objectToBuild->Instantiate();
		}
		//Add it to the active hub
		//easy peezy
	}
}

void BuildingController::AddTempObject(GameObject * object)
{
	objectToBuild = object;
}
