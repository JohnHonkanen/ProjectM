#include "PlayerEconManager.h"

PlayerEconManager::PlayerEconManager()
{
}

PlayerEconManager::~PlayerEconManager()
{
}

PlayerEconomy PlayerEconManager::AddEconomy(EconName econName, string nameOfEconomy)
{
	PlayerEconomy playerEconomy = PlayerEconomy(resourceManager, this, econName, nameOfEconomy);
	Resources resource = resourceManager->FindResource(ResourceName::Gold); // Add gold as a resource to player economy

	switch (econName) {
	case EconName::Player_Econ:
		this->econList[PLAYER_ECON] = playerEconomy;
		break;

	default:
		cout << "No Economy found" << endl;
		break;
	}

	return playerEconomy;
}

PlayerEconomy* PlayerEconManager::FindPlayerEcon(EconName econName)
{
	switch (econName) {
	case EconName::Player_Econ:
		return &econList[PLAYER_ECON];

	default:
		return nullptr;
	}
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
	GetCurrentGoldAmountIn(GetHUBInventory());

}

void PlayerEconManager::Start()
{
	econList.resize(1);
	AddEconomy(EconName::Player_Econ, "playerEcon");
}

void PlayerEconManager::SetHUBInventory(v2::Inventory * HUBInventory)
{
	this->HUBInventory = HUBInventory;
}

Inventory* PlayerEconManager::GetHUBInventory()
{
	return this->HUBInventory;
}

int PlayerEconManager::GetCurrentGoldAmountIn(v2::Inventory * inventory)
{
	return GetHUBInventory()->Contains(ResourceName::Gold);
}

vector<PlayerEconomy*> PlayerEconManager::GetList() const
{
	return vector<PlayerEconomy*>();
}
