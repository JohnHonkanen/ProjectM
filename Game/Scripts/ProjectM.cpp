#include "MobaJuiceCore.h"
#include "core\GameEngine.h"
#include "hud\HUD.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "Structure.h"
#include "Production.h"
#include "Warehouse.h"
#include "Inventory.h"
#include "CameraController.h"
#include "GameManager.h"
#include "BuildingController.h"
#include "hud\BuildingHUD.h"
#include "Production.h"
#include "hud\ContractHUD.h"
#include "hud\InventoryHUD.h"
#include "hud\HubHUD.h"
#include "Resources.h"
#include <iostream>
#include "PlayerActions.h"
#include "hud\PlayerEconHUD.h"
#include "hud\ProductionHUD.h"
#include "hud\MarketHUD.h"
#include "hud\SellHUD.h"

#include "Billboard.h"
#include "BuildingSpawnAnim.h"
#include "BuildingProductionAnims.h"
#include "hud\MainHUD.h"
#include "InventoryWrapper.h"
#include "Resources.h"
#include "components\Light.h"

#include "task_system\TaskManager.h"
#include "Dock.h"
#include "TradeShipSpawner.h"
#include "Hub.h"
#include "Drone.h"
#include "UnbuildableZone.h"
#include <stdlib.h> 

using namespace std;



int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine(false);
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) + "default-settings.xml").c_str());

	engine.manager.inputManager.AddKey("build", "b");

	Scene *scene = engine.CreateScene("TerrainScene");
	scene->AddSkyBox("Game/Assets/Skybox/Nebula/Nebula.tga");

	GameObjectManager *manager = scene->GetGameObjectManager();

	//Game Manager
	GameObject *gameManagerObject = manager->CreateGameObject("Game Manager");
	GameManager* gameManager = GameManager::Create(gameManagerObject); //Handles rules of the game. Boundaries etc

	//Terrain
	GameObject * terrain = manager->CreateGameObject("Terrain");
	Terrain::TerrainGrid *grid = Terrain::TerrainGrid::Create(terrain, 10, 300, 300, 0.003, 1, "terrainGridShader", true, vec3(0, 1, 0));
	Terrain::TerrainRenderer::Create(terrain, "Game/Assets/Textures/sand.png", "terrainShader");
	terrain->transform->Translate(vec3(-1000, 0, 0));

	//HUB
	int amount = 0;
	GameObject *hubObject = manager->CreateGameObject("HUB");

	Hub *hub = Hub::Create(hubObject, gameManager);
	hubObject->transform->Scale(vec3(100.0f));
	hubObject->transform->Rotate(vec3(0, 0, 0));
	hubObject->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	hubObject->transform->Translate(vec3(0, 15, 0));
	hubObject->material->diffuseMap = "Game/Assets/Textures/Models/Hub_UVW.png";
	hubObject->material->altDiffuseMap = "Game/Assets/Textures/Models/building_selected.jpg";
	//end of Hub Setup
	vec2 snapPoint = grid->GetCoordinates(vec3(0));
	snapPoint.x -= 5;
	snapPoint.y -= 1;
	for (int x = snapPoint.x; x < snapPoint.x + 10; x++)
	{
		for (int z = snapPoint.y; z < snapPoint.y + 7; z++)
		{
			hub->AddStructureToNetwork(HUB, hub, x, z);
		}
	}

	gameManager->SetHub(hub);

	////Setup some unbuildableZones
	GameObject *uZObject1 = manager->CreateGameObject("UnbuildableZ1");
	int startPosX = (rand() % 500 + -500), startPosZ = (rand() % 500 + -500);
	UnbuildableZone *unbuildableZone1 = UnbuildableZone::Create(uZObject1, gameManager);
	uZObject1->transform->Scale(vec3(50.0f));
	uZObject1->transform->Rotate(vec3(0, 0, 0));
	uZObject1->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	uZObject1->transform->Translate(vec3(startPosX, 0, startPosZ));
	uZObject1->material->diffuseMap = "Game/Assets/Textures/Rock/Rock_d.jpg";
	vec2 UZsnapPoint = grid->GetCoordinates(vec3(startPosX,0, startPosZ));
	// Set area on grid for building
	UZsnapPoint.x -= 5;
	UZsnapPoint.y -= 1;
	for (int x = UZsnapPoint.x; x < UZsnapPoint.x + 10; x++)
	{
		for (int z = UZsnapPoint.y; z < UZsnapPoint.y + 4; z++)
		{
			hub->AddStructureToNetwork(UNBUILDABLEZONE, unbuildableZone1, x, z);
		}
	}

	////Setup some unbuildableZones
	GameObject *uZObject2 = manager->CreateGameObject("UnbuildableZ2");
	startPosX = (rand() % 500 + -500), startPosZ = (rand() % 500 + -500);
	UnbuildableZone *unbuildableZone2 = UnbuildableZone::Create(uZObject2, gameManager);
	uZObject2->transform->Scale(vec3(50.0f));
	uZObject2->transform->Rotate(vec3(0, 0, 0));
	uZObject2->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	uZObject2->transform->Translate(vec3(startPosX, 0, startPosZ));
	uZObject2->material->diffuseMap = "Game/Assets/Textures/Rock/Rock_d.jpg";
	UZsnapPoint = grid->GetCoordinates(vec3(startPosX, 0, startPosZ));
	// Set area on grid for building
	UZsnapPoint.x -= 5;
	UZsnapPoint.y -= 1;
	for (int x = UZsnapPoint.x; x < UZsnapPoint.x + 10; x++)
	{
		for (int z = UZsnapPoint.y; z < UZsnapPoint.y + 4; z++)
		{
			hub->AddStructureToNetwork(UNBUILDABLEZONE, unbuildableZone2, x, z);
		}
	}

	////Setup some unbuildableZones
	GameObject *uZObject3 = manager->CreateGameObject("UnbuildableZ3");
    startPosX = (rand() % 500 + -500), startPosZ = (rand() % 500 + -500);
	UnbuildableZone *unbuildableZone3 = UnbuildableZone::Create(uZObject3, gameManager);
	uZObject3->transform->Scale(vec3(50.0f));
	uZObject3->transform->Rotate(vec3(0, 0, 0));
	uZObject3->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	uZObject3->transform->Translate(vec3(startPosX, 0, startPosZ));
	uZObject3->material->diffuseMap = "Game/Assets/Textures/Rock/Rock_d.jpg";
	UZsnapPoint = grid->GetCoordinates(vec3(startPosX, 0, startPosZ));
	// Set area on grid for building
	UZsnapPoint.x -= 5;
	UZsnapPoint.y -= 1;
	for (int x = UZsnapPoint.x; x < UZsnapPoint.x + 10; x++)
	{
		for (int z = UZsnapPoint.y; z < UZsnapPoint.y + 4; z++)
		{
			hub->AddStructureToNetwork(UNBUILDABLEZONE, unbuildableZone3, x, z);
		}
	}

	////Setup some unbuildableZones
	GameObject *uZObject4 = manager->CreateGameObject("UnbuildableZ3");
	startPosX = (rand() % 500 + -500), startPosZ = (rand() % 500 + -500);
	UnbuildableZone *unbuildableZone4 = UnbuildableZone::Create(uZObject4, gameManager);
	uZObject4->transform->Scale(vec3(50.0f));
	uZObject4->transform->Rotate(vec3(0, 0, 0));
	uZObject4->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	uZObject4->transform->Translate(vec3(startPosX, 0, startPosZ));
	uZObject4->material->diffuseMap = "Game/Assets/Textures/Rock/Rock_d.jpg";
	UZsnapPoint = grid->GetCoordinates(vec3(startPosX, 0, startPosZ));
	// Set area on grid for building
	UZsnapPoint.x -= 5;
	UZsnapPoint.y -= 1;
	for (int x = UZsnapPoint.x; x < UZsnapPoint.x + 10; x++)
	{
		for (int z = UZsnapPoint.y; z < UZsnapPoint.y + 4; z++)
		{
			hub->AddStructureToNetwork(UNBUILDABLEZONE, unbuildableZone4, x, z);
		}
	}

	////Setup some unbuildableZones
	GameObject *uZObject5 = manager->CreateGameObject("UnbuildableZ3");
	startPosX = (rand() % 500 + -500), startPosZ = (rand() % 500 + -500);
	UnbuildableZone *unbuildableZone5 = UnbuildableZone::Create(uZObject5, gameManager);
	uZObject5->transform->Scale(vec3(50.0f));
	uZObject5->transform->Rotate(vec3(0, 0, 0));
	uZObject5->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	uZObject5->transform->Translate(vec3(startPosX, 0, startPosZ));
	uZObject5->material->diffuseMap = "Game/Assets/Textures/Rock/Rock_d.jpg";
	UZsnapPoint = grid->GetCoordinates(vec3(startPosX, 0, startPosZ));
	// Set area on grid for building
	UZsnapPoint.x -= 5;
	UZsnapPoint.y -= 1;
	for (int x = UZsnapPoint.x; x < UZsnapPoint.x + 10; x++)
	{
		for (int z = UZsnapPoint.y; z < UZsnapPoint.y + 4; z++)
		{
			hub->AddStructureToNetwork(UNBUILDABLEZONE, unbuildableZone5, x, z);
		}
	}

	//Temp Code to make Structures
	GameObject * dome = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Dome", DOME, 10, 1, 1, 1, 300, 1,false, false, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Dome.DAE"
	);
	dome->material->diffuseMap = "Game/Assets/Textures/Models/Dome_UVW.png";

	GameObject * factory = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Factory", FACTORY, 10, 1, 1,1,500, 1, false, false, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Factory.DAE"
	);
	factory->material->diffuseMap = "Game/Assets/Textures/Models/Factory_UVW.png";

	GameObject * warehouse = gameManager->buildingManager.CreateNewBuilding(
		Warehouse::Create("Warehouse", 10, 1, 1, 1, false, false, &gameManager->resourceManager),
		"Game/Assets/Models/mobajuice/Warehouse.DAE"
	);
	warehouse->material->diffuseMap = "Game/Assets/Textures/Models/Warehouse_UVW.png";

	GameObject *dock = gameManager->buildingManager.CreateNewBuilding(
		Dock::Create(10, 150),
		"Game/Assets/Models/mobajuice/Dock.dae"
	);
	dock->material->diffuseMap = "Game/Assets/Textures/Models/dock_texture.png";

	//Player
	GameObject *focusPoint = manager->CreateGameObject("Camera Focus Point");
	//MeshRenderer::Create(focusPoint, "Game/Assets/Models/cube/cube.obj");
	focusPoint->transform->SetScale(vec3(3.0f));
	GameObject *playerObject = manager->CreateGameObject("Player");

	focusPoint->transform->AddChildren(playerObject->transform.get());
	Camera * c = Camera::Create(playerObject);
	c->SetFarClippingPlane(500.0f);
	c->SetFOV(60);
	CameraController::Create(playerObject, focusPoint->transform.get());
	BuildingController *buildingController = BuildingController::Create(playerObject, &gameManager->buildingManager, hub);
	buildingController->colHelper.SetGrid(grid); // Set the grid we want to register with
												 //Temp Function

	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 0, 0, 1280 , 720 }, "");

	PlayerActions* pla = buildingController->GetPlayerAction();
	//HUD GameObjects
	GameObject *hudController = manager->CreateGameObject("Hud Controller");
	ContractHUD* contractHUD = ContractHUD::Create(hudController, canvas, &gameManager->contractManager);
	MarketHUD::Create(hudController, canvas, &gameManager->marketManager);
	SellHUD * sellHUD = SellHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);
	MainHUD::Create(hudController, canvas, buildingController, contractHUD, sellHUD);
	//PlayerEconHUD::Create(hudController, canvas, &gameManager->playerEconManager);
	ProductionHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);
	InventoryHUD* inv = InventoryHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);


	HubHUD::Create(hudController, canvas, hub, &gameManager->resourceManager);


	//Trade Ship Spawner
	GameObject *tspObject = manager->CreateGameObject("tradeShipSpawner");
	auto tsp = TradeShipSpawner::Create(tspObject);

	gameManager->SetTradeShipSpawner(tsp);

	engine.Run();
	return 0;
}