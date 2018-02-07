
#include "MobaJuiceCore.h"
#include "ObjectPlacer.h"
#include "BuildingManager.h"
#include "Structure.h"
#include "Production.h"
#include "Warehouse.h"

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine();
	//engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) +  "   default-settings.xml").c_str());
	Scene *scene = engine.CreateScene("BlankScene"); // Declares a game scene
	GameObjectManager *manager = scene->GetGameObjectManager(); // Grabs the game object manager from the engine
	GameObject *structure = manager->CreateGameObject("Cube_1500"); 
	// Sets up a game object called structure. The CreateGameObject method registers the object.
	Structure::Create("hub", 10, 5, 3, 1, vec3(1.0f), true, false);
	// Adds a structure component to the structure game object.
	// Takes the game object, the structure type, the structure's health points, it's power usage, 
	//it's production efficiency, it's radiation output, it's position, whether or not it is placed 
	// and whether or not it is active as parameters.

	/// NOTES & Things to change? ///
	/*
	1) The type of structure that the structure will become is not as presently handled in any way by the 
	methods in the class - This will need to be nailed down.

	2) The initial position might not be needed as below the engine methods can handle that with a global 
	transformation which might work better because we won't need to worry about it's placement in the game 
	space, that would be handled by whereever the mouse happens to be for example and those coordinates
	are extrapolated from there.

	3) I'm assuming that when the building is initially placed we should not assume it is powered as it 
	may be being placed off of the grid that has power. We will need another method to determine if it
	should be powered and it could pass it's result to the constructor? - This could get complicated quick 
	depending on the route we decide to take.

	4) It might be useful to just have a table of declared values to put into the constructor. Say for example we 
	want a Hub, when the "hub" string is passed into the constructor a method will detect this and pass all the neccesary
	values to the real constructor. A pseudo wrapper constructor? Or one that takes only that one parameter but has
	the big one nested inside it? - What do you think?

	Of course that is just ease of use for us when we decide to mega test it. For now we might want to keep it on the 
	more basic side until it gets working.

	5) Doesn't seem to be loading the assets properly atm. I took the assets from the old liquid compass as they 
	contained the cube and sand obj and texture... Will need to ask about that one I think...
	*/
	///// End of Notes //////

	MeshRenderer::Create(structure, "Assets/Models/cube/cube.obj");
	// Creates a mesh for the structure with ther specified asset file.
	TextureSetter::Create(structure, "Assets/Textures/sand.png");
	// Sets a texture for the structure with the specified texture.

	structure->transform->SetScale(vec3(5.0f));
	engine.Run();
	return 0;
}