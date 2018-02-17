
#include "MobaJuiceCore.h"
#include "core\GameEngine.h"
#include "hud\HUD.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"
#include "CameraController.h"
#include "GameManager.h"

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
	GameManager* gameManager =  GameManager::Create(gameManagerObject);

	//Terrain
	GameObject * terrain = manager->CreateGameObject("Terrain");
	Terrain::TerrainGrid *grid = Terrain::TerrainGrid::Create(terrain, 10, 150, 150, 0.003, 10, "terrainGridShader", true, vec3(0, 1, 0));
	Terrain::TerrainRenderer::Create(terrain, "Game/Assets/Textures/ground.jpg", "terrainShader");

	//Player
	GameObject *playerObject = manager->CreateGameObject("Player");
	Camera * c = Camera::Create(playerObject);
	c->SetFarClippingPlane(1000.0f);
	CameraController::Create(playerObject);


	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 300, 10, 640 , 360 }, "");
	HUD::WHUDContainer * container = HUD::WHUDContainer::Create(canvas, { 100 , 100, 100, 100 }, "Game/Assets/Textures/ground.jpg", true);
	HUD::TextWidget *text = HUD::TextWidget::Create(canvas, { 0, 50, 100, 100 }, "Cow and Chicken", "Game/Assets/Fonts/MavenPro-Regular.ttf", 48, 1, vec3(1, 0, 1));

	engine.Run();
	return 0;
}