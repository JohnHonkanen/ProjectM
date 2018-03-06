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

	playerEconomy.name = "pEcon";
	this->economyList[0] = playerEconomy;

	return this->economyList[0];
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
	this->economyList[0] = playerEconomy;
}

void PlayerEconManager::Start()
{
	AddEconomy();
}
