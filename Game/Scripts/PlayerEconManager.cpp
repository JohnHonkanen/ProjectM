#include "PlayerEconManager.h"

PlayerEconManager::PlayerEconManager()
{
}

PlayerEconManager::~PlayerEconManager()
{
}

PlayerEconomy PlayerEconManager::AddEconomy()
{
	Resources resource = resourceManager->FindResource(0);
	PlayerEconomy playerEconomy = PlayerEconomy(resource, this);

	cout << "Economy resource name: " << resource.GetItemID() << endl;
	return this->economyList[0] = playerEconomy;;
}

PlayerEconomy * PlayerEconManager::FindPlayerEcon()
{
	return this->playerEconomy;
}

void PlayerEconManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
}

void PlayerEconManager::Update()
{
}

void PlayerEconManager::Start()
{
	AddEconomy();
}
