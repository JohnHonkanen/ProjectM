#include "PlayerEconManager.h"

PlayerEconManager::PlayerEconManager()
{
}

PlayerEconManager::~PlayerEconManager()
{
}

PlayerEconomy PlayerEconManager::AddEconomy()
{
	PlayerEconomy playerEconomy = PlayerEconomy(resourceManager, this);
	Resources resource = resourceManager->FindResource(0); // Add gold as a resource to player economy

	playerEconomy.SetPlayerEconIndex(0);
	playerEconomy.name = "pEcon";

	this->economyList[playerEconomy.GetPlayerEconIndex()] = playerEconomy;

	return this->economyList[playerEconomy.GetPlayerEconIndex()];
}

PlayerEconomy* PlayerEconManager::FindPlayerEcon()
{
	
	return &this->economyList[0];
}


void PlayerEconManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

PlayerEconManager * PlayerEconManager::Create(GameObject * gameObject)
{
	PlayerEconManager *p = new PlayerEconManager();
	gameObject->AddComponent(p);
	return p;
}

void PlayerEconManager::Copy(GameObject * copyObject)
{
	// Does nothing
}

void PlayerEconManager::OnLoad()
{
	
}

void PlayerEconManager::Update()
{
	

}

void PlayerEconManager::Start()
{
	AddEconomy();
}
