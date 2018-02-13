#include "core\GameEngine.h"
#include "MobaJuiceCore.h"
#include "ObjectPlacer.h"
#include "BuildingManager.h"
#include "Structure.h"
#include "Production.h"
#include "Warehouse.h"

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine();
	engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) + "default-settings.xml").c_str());
	Scene *scene = engine.CreateScene("BlankScene"); // Declares a game scene
													 //engine.Load("TerrainScene.xml");
													 //Scene *scene = engine.GetActiveScene();
	scene->AddSkyBox("Assets/Skybox/Nebula/Nebula.tga");
	GameObjectManager *manager = scene->GetGameObjectManager(); // Grabs the game object manager from the engine
	GameObject * camera = manager->Find("camera");
	Terrain::TerrainSnapper * tSnapper = camera->GetComponent<TerrainSnapper>();

	GameObject *structure = manager->CreateGameObject("Cube_1500");
	// Sets up a game object called structure. The CreateGameObject method registers the object.
	//Structure::Create("hub", 10, 5, 3, 1, vec3(1.0f), true, false);
	// Adds a structure component to the structure game object.
	// Takes the game object, the structure type, the structure's health points, it's power usage, 
	// it's production efficiency, it's radiation output, it's position, whether or not it is placed 
	// and whether or not it is active as parameters.

	MeshRenderer::Create(structure, "Assets/Models/cube/cube.obj");
	// Creates a mesh for the structure with ther specified asset file.
	TextureSetter::Create(structure, "Assets/Textures/sand.png");
	// Sets a texture for the structure with the specified texture.

	structure->transform->SetScale(vec3(5.0f));

	tSnapper->SetHeldObject(structure);

	ObjectPlacer::Create(camera, structure, tSnapper);

	GameObject * terrain = manager->Find("Terrain");
	Terrain::TerrainGrid *grid = terrain->GetComponent<Terrain::TerrainGrid>();

	tSnapper->grid = grid;

	engine.Run();
	return 0;
}