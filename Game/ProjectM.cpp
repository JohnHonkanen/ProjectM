#pragma once

#include "MobaJuiceCore.h"
#include "Scripts\Resources.h"
#include "Scripts\ResourceManager.h"
#include "Scripts\PlayerEconomy.h"
#include "Scripts\Contract.h"
#include "core\GameEngine.h"
#include "Scripts\ContractManager.h"

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

	GameObject* contractManager = gameObjectManager->CreateGameObject("contractManager");
	ContractManager::Create(contractManager);

	engine.Run();

	return 0;
}