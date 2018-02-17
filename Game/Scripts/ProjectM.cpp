
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

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine(true);
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
	HUD::TextWidget *text = HUD::TextWidget::Create(canvas, { 0, 50, 100, 100 }, "Cow and Chicken", "Game/Assets/Fonts/MavenPro-Regular.ttf", 48, 1, vec3(1,0,1));


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

	engine.Run();
	return 0;
}