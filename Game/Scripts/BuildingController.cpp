#include "BuildingController.h"
#include "core\GameEngine.h"
#include "Hub.h"
#include "PlayerActions.h"
#include "DroneProducer.h"
#include "GameManager.h"
#include "LightCycle.h"
BuildingController::~BuildingController()
{
}

BuildingController * BuildingController::Create(GameObject * gameObject, BuildingManager * buildingManager, Hub *hub)
{
	BuildingController *bc = new BuildingController();
	bc->buildingManager = buildingManager;
	bc->hub = hub;

	bc->playerAction = PlayerActions::Create(gameObject, bc, hub);
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
	Structure *sComp = objectToBuild->GetComponent<Structure>();
	objectToBuild->transform->Rotate(vec3(-90, 0, 0));
	objectToBuild->transform->Scale(vec3(10) * float(sComp->GetTileWidth()));

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
					Structure *sComp = objectToBuild->GetComponent<Structure>();
					float tileWidth = float(sComp->GetTileWidth());

					if (FindStructure(coordinates.x, coordinates.y, tileWidth) == nullptr)
					{
						GameObject * structure = buildingManager->GetBuilding(structureName);
						Structure *sComponent = structure->GetComponent<Structure>();
						structure->GetComponent<LightCycle>()->ActivateLight();
						mouseHeld = true;
						sComponent->SetTilePosition(coordinates.x, coordinates.y);
						sComponent->SetActive(false); //Turn on structures
						RegisterToNetwork(sComponent, coordinates.x, coordinates.y, tileWidth);
						structure->transform->SetPosition(snapPoint);
						float yTrans = -5.0f;
						switch (sComponent->GetType())
						{
						case DOCK:
								yTrans = -3.5f;
								sComponent->SetActive(true);
								break;
						case FACTORY:
							yTrans = -8.0f;
							break;
						}
						
						structure->transform->Translate(vec3(0, yTrans, 0));
						structure->transform->Rotate(vec3(-90,0,0));
						structure->transform->Scale(vec3(10) * float(sComponent->GetTileWidth()));

						GameManager::gameManager->playerEconManager.FindPlayerEcon(EconName::Player_Econ)->RemoveGoldBars(sComponent->GetCost());
						buildMode = false;
					}
					else {
						printf("Slot Taken \n");
					}
					
				}
				
				
			}
			else {
				mouseHeld = false;
			}
			if (GameEngine::manager.inputManager.GetKey("mouse1"))
			{
				buildMode = false;
			}
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

bool BuildingController::GetBuildMode()
{
	return buildMode;
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

PlayerActions * BuildingController::GetPlayerAction()
{
	return playerAction;
}

Structure * BuildingController::FindStructure(float x, float y, float width)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + width; j++)
		{
			Structure * s = hub->GetStructure(i, j);
			if (s != nullptr)
			{
				return s;
			}
		}
	}

	return nullptr;
}

void BuildingController::RegisterToNetwork(Structure * s, float x, float y, float width)
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + width; j++)
		{
			hub->AddStructureToNetwork(s->GetType(),s, i, j);
		}
	}

	hub->AddStructureToList(s->GetType(), s, x, y);
}
