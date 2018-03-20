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
	marketManager.OnLoad();
	GameEngine::manager.shaderManager.CreateShader("billboard", "Game/Shaders/billboard.vert", "Game/Shaders/billboard.frag");
}

void GameManager::Start()
{
	contractManager.SetManager(&resourceManager);
	contractManager.SetManager(&playerEconManager);
	contractManager.Start();

	playerEconManager.SetResourceManager(&resourceManager);
	playerEconManager.Start();

	marketManager.SetResourceManager(&resourceManager);
	marketManager.Start();
}

void GameManager::Update()
{
	resourceManager.Update();
	contractManager.Update();
	playerEconManager.Update();
	marketManager.Update();
}
