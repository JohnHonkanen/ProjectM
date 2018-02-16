
#include "MobaJuiceCore.h"
#include "core\GameEngine.h"
#include "hud\HUD.h"
#include "hud\HUDCanvas.h"
#include "hud\widgets\HUDContainer.h"
#include "hud\widgets\TextWidget.h"

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine();
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) + "default-settings.xml").c_str());

	engine.manager.inputManager.AddKey("build", "b");

	Scene *scene = engine.CreateScene("TerrainScene");
	scene->AddSkyBox("Game/Assets/Skybox/Nebula/Nebula.tga");

	GameObjectManager *manager = scene->GetGameObjectManager();

	GameObject * camera = manager->CreateGameObject("camera");
	Camera * c = Camera::Create(camera);
	c->SetFarClippingPlane(1000.0f);
	FreeCameraControl::Create(camera);

	/*GameObject * text = manager->CreateGameObject("text");
	Text2D::Create(text, "text2D", "Pre-alpha build 0.2.1.3", {255, 255, 255}, "Assets/Fonts/MavenPro-Regular.ttf");
	text->transform->Scale(vec3(200, 20, 0));
	text->transform->Translate(vec3(220, 700, 0));*/

	//Add HUD
	HUD::HUD * hud = HUD::HUD::Create(scene, 1280, 720);
	HUD::HUDCanvas * canvas = HUD::HUDCanvas::Create(hud, { 300, 10, 640 , 360 }, "");
	HUD::WHUDContainer * container = HUD::WHUDContainer::Create(canvas, { 100 , 100, 100, 100 }, "Game/Assets/Textures/ground.jpg", true);
	HUD::TextWidget *text = HUD::TextWidget::Create(canvas, { 0, 50, 100, 100 }, "Cow and Chicken", "Game/Assets/Fonts/MavenPro-Regular.ttf", 48, 1, vec3(1, 0, 1));


	GameObject * terrain = manager->CreateGameObject("Terrain");
	Terrain::TerrainGrid *grid = Terrain::TerrainGrid::Create(terrain, 10, 150, 150, 0.003, 10, "terrainGridShader", true, vec3(0, 1, 0));
	Terrain::TerrainRenderer::Create(terrain, "Game/Assets/Textures/ground.jpg", "terrainShader");
	Terrain::TerrainSnapper * tSnapper = Terrain::TerrainSnapper::Create(camera, grid);

	{
		GameObject *rock = manager->CreateGameObject("Cube");
		MeshRenderer::Create(rock, "Game/Assets/Models/cube/cube.obj");
		TextureSetter::Create(rock, "Game/Assets/Textures/sand.png");
		rock->transform->SetScale(vec3(5.0f));
	}

	{
		for (int i = 0; i < 100; i++) {
			GameObject *rock = manager->CreateGameObject("rock" + to_string(i));
			MeshRenderer::Create(rock, "Game/Assets/Models/rock/Rock.obj");
			TextureSetter::Create(rock, "Game/Assets/Textures/Rock/Rock_d.jpg");
			rock->transform->SetScale(vec3(0.3f));
			rock->transform->Rotate(vec3(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50));
			int x = rand() % 150 - 75;
			int z = rand() % 150 - 75;
			rock->transform->SetPosition(x * 10, grid->GetHeight(x, z) - rand() % 10, z * 10);
		}

	}


	engine.Run();
	return 0;
}