
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

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine(true);
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) + "default-settings.xml").c_str());

	engine.manager.inputManager.AddKey("build", "b");

	Scene *scene = engine.CreateScene("TerrainScene");
	scene->AddSkyBox("Game/Assets/Skybox/Nebula/Nebula.tga");

	GameObjectManager *manager = scene->GetGameObjectManager();

	//Game Manager
	GameObject *gameManagerObject = manager->CreateGameObject("Game Manager");
	GameManager* gameManager =  GameManager::Create(gameManagerObject); //Handles rules of the game. Boundaries etc

	//Temp Code to make Structures
	GameObject * dome = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Dome", "Basic Factory", 10, 1, 1, 1, false, false),
		"Game/Assets/Models/cube/cube.obj"
	);
	dome->material->diffuseMap = "Game/Assets/Textures/sand.png";

	GameObject * factory = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Factory", "Basic Factory", 10, 1, 1, 1, false, false),
		"Game/Assets/Models/cube/cube.obj"
	);
	factory->material->diffuseMap = "Game/Assets/Textures/building_hud.jpg";

	GameObject * warehouse = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Warehouse", "Basic Factory", 10, 1, 1, 1, false, false),
		"Game/Assets/Models/cube/cube.obj"
	);
	warehouse->material->diffuseMap = "Game/Assets/Textures/ground.jpg";


	//End of Temp Code


	//Terrain
	GameObject * terrain = manager->CreateGameObject("Terrain");
	Terrain::TerrainGrid *grid = Terrain::TerrainGrid::Create(terrain, 10, 150, 150, 0.003, 10, "terrainGridShader", true, vec3(0, 1, 0));
	Terrain::TerrainRenderer::Create(terrain, "Game/Assets/Textures/ground.jpg", "terrainShader");

	//Temp Object to Test Building Manager
	GameObject *structure = manager->CreateGameObject("Temp Structure");
	MeshRenderer::Create(structure, "Game/Assets/Models/cube/cube.obj");
	TextureSetter::Create(structure, "Game/Assets/Textures/sand.png");
	structure->transform->SetScale(vec3(5.0f));

	//Player
	GameObject *playerObject = manager->CreateGameObject("Player");
	Camera * c = Camera::Create(playerObject);
	c->SetFarClippingPlane(1000.0f);
	CameraController::Create(playerObject);
	BuildingController *buildingController = BuildingController::Create(playerObject, &gameManager->buildingManager);
	buildingController->colHelper.SetGrid(grid); // Set the grid we want to register with
	//Temp Function
	buildingController->AddTempObject(structure);


	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 0, 0, 1280 , 720 }, "");

	}
	
	Resources res1 = Resources(1, "1stMeat ", "Meat ", 5, 50);
	Resources res2 = Resources(1, "2ndMeat ", "Meat ", 5, 51);

	Resources res3 = Resources(3, "box ", "BigBox ", 5, 1);
	Resources res4 = Resources(4, "box ", "BigBox ", 5, 1);
	Resources res5 = Resources(5, "box ", "BigBox ", 5, 1);
	Resources res6 = Resources(6, "box ", "BigBox ", 5, 1);
	Resources res7 = Resources(7, "box ", "BigBox ", 5, 1);
	Resources res8 = Resources(8, "box ", "BigBox ", 5, 1);
	Resources res9 = Resources(9, "box ", "BigBox ", 5, 1);
	Resources res10 = Resources(10, "box ", "BigBox ", 5, 1);
	
	GameObject *warehouse = manager->CreateGameObject("Warehouse");
	Warehouse *w = Warehouse::Create(warehouse, "Warehouse", 10, 1, 1, 1, true, true);

	cout << w->ViewInventory() << endl; // Printing when empty.

	w->InsertItem(res1); // Inserting resources with the same ID who add into each other.
	w->InsertItem(res2);

	cout << w->ViewInventory() << endl; // Displaying added values.

	w->InsertItem(res3);
	w->InsertItem(res4);
	w->InsertItem(res5);
	w->InsertItem(res6);
	w->InsertItem(res7);
	w->InsertItem(res8);
	w->InsertItem(res9);
	w->InsertItem(res10); // Hits storage is full error.

	cout << w->ViewInventory() << endl; // Displaying full inventory.

	//HUD GameObjects
	GameObject *hudController = manager->CreateGameObject("Hud Controller");
	BuildingHUD::Create(hudController, canvas, &gameManager->buildingManager, buildingController);
	ContractHUD::Create(hudController, canvas, &gameManager->contractManager);

	engine.Run();
	return 0;
}