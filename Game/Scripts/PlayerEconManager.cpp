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

	cout << "Economy resource name: " << resource.GetName() << endl;
	this->economyList[0] = playerEconomy;

	return this->economyList[0];
}

PlayerEconomy * PlayerEconManager::FindPlayerEcon()
{
	
	return &this->economyList[0];
}

void PlayerEconManager::SetResourceManager(ResourceManager * resourceManager)
{
	this->resourceManager = resourceManager;
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
