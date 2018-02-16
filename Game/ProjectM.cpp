#pragma once

#include "MobaJuiceCore.h"
#include "Scripts\Resources.h"
#include "Scripts\ResourceManager.h"
#include "Scripts\PlayerEconomy.h"
#include "Scripts\Contract.h"
#include "core\GameEngine.h"

int main(int argc, char *argv[])
{
	GameEngine engine = GameEngine();
	//engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) +  "default-settings.xml").c_str());
	Scene *scene = engine.CreateScene("BlankScene");
	
	GameObjectManager* gameObjectManager = scene->GetGameObjectManager();

	PlayerEconomy playerEconomy = PlayerEconomy();
	playerEconomy.Init();

	GameObject* resourceManager = gameObjectManager->CreateGameObject("resourceManager");
	ResourceManager::Create(resourceManager);


	GameObject* contract = gameObjectManager->CreateGameObject("contract");
	Contract* c = Contract::Create(contract);
	c->GenerateContract();

	engine.Run();

	return 0;
}