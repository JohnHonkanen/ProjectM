#include "GameManager.h"

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
}

void GameManager::Start()
{
	contractManager.SetResourceManager(&resourceManager);
	contractManager.Start();
}

void GameManager::Update()
{
	resourceManager.Update();
	contractManager.Update();
}
