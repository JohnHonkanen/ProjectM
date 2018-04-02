#include "GameManager.h"
#include "core\GameEngine.h"
#include "TradeShipSpawner.h"

GameManager *GameManager::gameManager = nullptr;
GameManager * GameManager::Create(GameObject * gameObject)
{
	GameManager *gm = new GameManager();

	if (gameManager == nullptr)
		gameManager = gm;

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
	recipeManager.OnLoad();
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

void GameManager::SetHub(Hub * in_hub)
{
	hub = in_hub;
}

Hub * GameManager::GetHub() const
{
	return hub;
}

void GameManager::SetTradeShipSpawner(TradeShipSpawner * spawner)
{
	tradeShipSpawner = spawner;
}

TradeShipSpawner * GameManager::GetTradeShipSpawner() const
{
	return tradeShipSpawner;
}
