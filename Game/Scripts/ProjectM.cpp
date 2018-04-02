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

using namespace std;

#include "Hub.h"
#include "Drone.h"

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
	hubObject->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";
	hubObject->material->altDiffuseMap = "Game/Assets/Textures/building_selected.jpg";
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

	//Temp Code to make Structures
	GameObject * dome = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Dome", DOME, 10, 1, 1, 2, 100, 1,false, false, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Dome.DAE"
	);
	dome->material->diffuseMap = "Game/Assets/Textures/Dome_UVW.png";

	GameObject * factory = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Factory", FACTORY, 10, 1, 1,2,100, 1, false, false, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Factory.DAE"
	);
	factory->material->diffuseMap = "Game/Assets/Textures/factory_UVW.png";

	GameObject * warehouse = gameManager->buildingManager.CreateNewBuilding(
		Warehouse::Create("Warehouse", 10, 1, 1, 1, false, false, &gameManager->resourceManager),
		"Game/Assets/Models/mobajuice/Warehouse.DAE"
	);
	warehouse->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";

	GameObject *dock = gameManager->buildingManager.CreateNewBuilding(
		Dock::Create(),
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
	MainHUD::Create(hudController, canvas, buildingController, contractHUD);
	//PlayerEconHUD::Create(hudController, canvas, &gameManager->playerEconManager);
	ProductionHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);
	

	InventoryHUD* inv = InventoryHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);

	HubHUD::Create(hudController, canvas, hub, &gameManager->resourceManager);

	//Directional Light
	GameObject *dirLightObj = manager->CreateGameObject("dirLight");
	MeshRenderer::Create(dirLightObj, "Game/Assets/Models/cube/cube.obj", DEFERRED);
	Light * dirLight =Light::Create(dirLightObj, DIRECTIONAL_LIGHT);
	LightProperties dirProp = {
		DIRECTIONAL_LIGHT,
		vec3(0.5f),
		vec3(0.5f),
		vec3(0.05f),

		1.0f, 0.1f, 3.0f
	};

	dirLight->SetLightProperties(dirProp);

	dirLightObj->transform->SetPosition(vec3(10000000, 10000000,1000000));
	dirLightObj->material->diffuseMap = "Game/Assets/Textures/building_selected.jpg";

	GameObject *p1 = manager->CreateGameObject("p1");
	Light * pointLight = Light::Create(p1, POINT_LIGHT);
	LightProperties pointProp = {
		POINT_LIGHT,
		vec3(1.0f),
		vec3(1.0f),
		vec3(0.15f),

		1.0f, 0.07f, 0.017f
	};
	pointLight->SetLightProperties(pointProp);
	p1->transform->SetPosition(vec3(-23,5,1));

	GameObject * trader = manager->CreateGameObject("trader");
	MeshRenderer::Create(trader, "Game/Assets/Models/mobajuice/Trader.dae");
	trader->material->diffuseMap = "Game/Assets/Textures/building_selected.jpg";
	trader->transform->Translate(vec3(-300, 300, 50));
	trader->transform->Scale(vec3(500));
	trader->transform->Rotate(vec3(-90, 0, 0));

	//Trade Ship Spawner
	GameObject *tspObject = manager->CreateGameObject("tradeShipSpawner");
	auto tsp = TradeShipSpawner::Create(tspObject);

	gameManager->SetTradeShipSpawner(tsp);

	engine.Run();
	return 0;
}