
#include "MobaJuiceCore.h"
#include "core\GameEngine.h"
#include "hud\HUD.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "CameraController.h"
#include "GameManager.h"
#include "BuildingController.h"
#include "hud\BuildingHUD.h"
#include "Production.h"
#include "hud\ContractHUD.h"
#include "Warehouse.h"
#include "Hub.h"
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
	GameManager* gameManager =  GameManager::Create(gameManagerObject); //Handles rules of the game. Boundaries etc

	//Temp Code to make Structures
	GameObject * dome = gameManager->buildingManager.CreateNewBuilding(
		Production::Create("Dome", "Basic Factory", 10, 1, 1, 1, false, true),
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

	//HUB
	GameObject *hubObject = manager->CreateGameObject("HUB");
	MeshRenderer::Create(hubObject, "Game/Assets/Models/cube/cube.obj");
	Hub *hub = Hub::Create(hubObject);
	hubObject->transform->Scale(vec3(5.0f));
	hubObject->transform->SetPosition(grid->GetSnapPoint(vec3(0)));
	hubObject->material->diffuseMap = "Game/Assets/Textures/building_placeholder.jpg";

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
	BuildingController *buildingController = BuildingController::Create(playerObject, &gameManager->buildingManager, hub);
	buildingController->colHelper.SetGrid(grid); // Set the grid we want to register with
	//Temp Function
	buildingController->AddTempObject(structure);


	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 0, 0, 1280 , 720 }, "");

	//HUD GameObjects
	GameObject *hudController = manager->CreateGameObject("Hud Controller");
	BuildingHUD::Create(hudController, canvas, &gameManager->buildingManager, buildingController);
	ContractHUD::Create(hudController, canvas, &gameManager->contractManager);

	engine.Run();
	return 0;
}