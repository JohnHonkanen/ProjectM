
#include "MobaJuiceCore.h"
#include "core\GameEngine.h"

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine();
	//engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) +  "default-settings.xml").c_str());
	Scene *scene = engine.CreateScene("BlankScene");
	engine.Run();
	return 0;
}