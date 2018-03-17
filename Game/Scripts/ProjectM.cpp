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
#include "Resources.h"
#include <iostream>
#include "PlayerActions.h"
#include "hud\PlayerEconHUD.h"
#include "hud\ProductionHUD.h"

#include "Billboard.h"
#include "BuildingSpawnAnim.h"
#include "BuildingProductionAnims.h"
#include "hud\MainHUD.h"
#include "InventoryWrapper.h"
#include "Resources.h"

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
	Terrain::TerrainGrid *grid = Terrain::TerrainGrid::Create(terrain, 10, 150, 150, 0.003, 1, "terrainGridShader", true, vec3(0, 1, 0));
	Terrain::TerrainRenderer::Create(terrain, "Game/Assets/Textures/terrain2.jpg", "terrainShader");

	//HUB
	int amount = 0;
	GameObject *hubObject = manager->CreateGameObject("HUB");
	InventoryWrapper * iw = InventoryWrapper::Create(hubObject, &gameManager->resourceManager);
	gameManager->playerEconManager.SetHUBInventory(&iw->inventory);
	iw->inventory.AddFilter(ResourceName::Gold);
	iw->inventory.SetMode(v2::Inventory::WHITELIST);
	iw->inventory.AddItem(ResourceName::Gold, 100);
	MeshRenderer * hubRenderer = MeshRenderer::Create(hubObject, "Game/Assets/Models/mobajuice/Hub.DAE");

	Hub *hub = Hub::Create(hubObject);
	hubObject->transform->Scale(vec3(3.0f));
	hubObject->transform->Rotate(vec3(0, 0, 0));
	hubObject->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	hubObject->transform->Translate(vec3(100, 8, 0));
	hubObject->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";
	hubObject->material->altDiffuseMap = "Game/Assets/Textures/building_selected.jpg";

	//Temp Code to make Structures
	GameObject * dome = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Dome", DOME, 10, 1, 1, 2, 100, 1,false, true, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Dome.DAE"
	);
	dome->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";

	GameObject * factory = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Factory", FACTORY, 10, 1, 1,2,100, 1, false, false, &gameManager->resourceManager, hub),
		"Game/Assets/Models/mobajuice/Factory.DAE"
	);
	factory->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";

	GameObject * warehouse = gameManager->buildingManager.CreateNewBuilding(
		Warehouse::Create("Warehouse", 10, 1, 1, 1, false, false, &gameManager->resourceManager),
		"Game/Assets/Models/mobajuice/Warehouse.DAE"
	);
	warehouse->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";

	//Temp Object to Test Building Manager
	GameObject *structure = manager->CreateGameObject("Temp Structure");
	MeshRenderer::Create(structure, "Game/Assets/Models/cube/cube.obj");
	TextureSetter::Create(structure, "Game/Assets/Textures/sand.png");
	structure->transform->SetScale(vec3(5.0f));

	//Player
	GameObject *focusPoint = manager->CreateGameObject("Camera Focus Point");
	MeshRenderer::Create(focusPoint, "Game/Assets/Models/cube/cube.obj");
	focusPoint->transform->SetScale(vec3(3.0f));
	GameObject *playerObject = manager->CreateGameObject("Player");

	focusPoint->transform->AddChildren(playerObject->transform.get());
	Camera * c = Camera::Create(playerObject);
	c->SetFarClippingPlane(1000.0f);
	CameraController::Create(playerObject, focusPoint->transform.get());
	BuildingController *buildingController = BuildingController::Create(playerObject, &gameManager->buildingManager, hub);
	buildingController->colHelper.SetGrid(grid); // Set the grid we want to register with
												 //Temp Function
	buildingController->AddTempObject(structure);

	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 0, 0, 1280 , 720 }, "");

	Warehouse* w = warehouse->GetComponent<Warehouse>();
	Warehouse* w2 = warehouse->GetComponent<Warehouse>();

	PlayerActions* pla = buildingController->GetPlayerAction();
	//HUD GameObjects
	GameObject *hudController = manager->CreateGameObject("Hud Controller");
	ContractHUD* contractHUD = ContractHUD::Create(hudController, canvas, &gameManager->contractManager);
	MainHUD::Create(hudController, canvas, buildingController, contractHUD);
	PlayerEconHUD::Create(hudController, canvas, &gameManager->playerEconManager);
	ProductionHUD::Create(hudController, canvas, pla);

	//Drone Code
	GameObject *droneObject = manager->CreateGameObject("drone");
	MeshRenderer::Create(droneObject, "Game/Assets/Models/mobajuice/Drone.DAE");
	Drone *drone = Drone::Create(droneObject);
	drone->SetDestination(vec3(250, 0, 150));
	droneObject->material->diffuseMap = "Game/Assets/Textures/building_placeholder.jpg";
	droneObject->transform->Scale(vec3(3));
	
	InventoryHUD* inv = InventoryHUD::Create(hudController, canvas, pla, &gameManager->resourceManager);
	//vector<Inventory*> iStorage;

	engine.Run();
	return 0;
}