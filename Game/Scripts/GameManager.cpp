#include "GameManager.h"
#include "core\GameEngine.h"

GameManager * GameManager::Create(GameObject * gameObject)
{
	GameManager *gm = new GameManager();

	gameObject->AddComponent(gm);

	return gm;
}

void GameManager::Copy(GameObject * copyObject)
{
	//Never needs to by copied
}

void GameManager::OnLoad()
{
	resourceManager.OnLoad();
	playerEconManager.OnLoad();
	GameEngine::manager.shaderManager.CreateShader("billboard", "Game/Shaders/billboard.vert", "Game/Shaders/billboard.frag");
}

void GameManager::Start()
{
	contractManager.SetResourceManager(&resourceManager);
	contractManager.Start();

	playerEconManager.SetResourceManager(&resourceManager);
	playerEconManager.Start();
}

void GameManager::Update()
{
	resourceManager.Update();
	contractManager.Update();
	playerEconManager.Update();
}
