#include "PlayerEconomy.h"
#include "PlayerEconManager.h"
#include "GameManager.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::PlayerEconomy(ResourceManager* resourceManager, PlayerEconManager* playerEconManager)
{
	this->resourceManager = resourceManager;
	this->playerEconManager = playerEconManager;
}

PlayerEconomy::PlayerEconomy(ResourceManager * resourceManager, PlayerEconManager * playerEconManager, EconName econName, string nameOfEcon)
{
	this->resourceManager = resourceManager;
	this->playerEconManager = playerEconManager;
	this->econName = econName;
	this->nameOfEcon = nameOfEcon;
}

PlayerEconomy::PlayerEconomy(const PlayerEconomy & copy)
{
	this->resourceManager = copy.resourceManager;
	this->playerEconManager = copy.playerEconManager;
	this->econName = copy.econName;
	this->nameOfEcon = copy.nameOfEcon;
}

PlayerEconomy::~PlayerEconomy()
{
}

void PlayerEconomy::GiveGoldBars(int amountToGive)
{
	//this->resource.SetItemAmount(amountToGive);
}

void PlayerEconomy::AddGoldBars(int goldBars)
{
	int debt = GameManager::gameManager->playerEconManager.GetCurrentDebtAmount();

	playerEconManager->HUBInventory->AddItem(ResourceName::Gold, goldBars - debt);
	playerEconManager->HUBInventory->CheckStorageFull(ResourceName::Gold);
}

 //Depricated
void PlayerEconomy::RemoveGoldBars(int goldBars)
{
	if (playerEconManager->HUBInventory->Contains(ResourceName::Gold) >= goldBars) {
		playerEconManager->HUBInventory->Remove(ResourceName::Gold, goldBars);
	}
}

void PlayerEconomy::SetGBAmount(int GBAmount)
{
	this->resource.SetItemAmount(GBAmount);
}

void PlayerEconomy::SetPlayerEconIndex(int indexToSet)
{
	this->index = indexToSet;
}

int PlayerEconomy::GetPlayerEconIndex()
{
	return this->index;
}

int PlayerEconomy::GetGBAmount()
{
	return playerEconManager->HUBInventory->Contains(ResourceName::Gold);
}

Resources PlayerEconomy::GetResouce()
{
	return this->resource;
}

string PlayerEconomy::GetGBIcon()
{
	return this->resource.GetResourceIcon();
}

vector<PlayerEconomy>& PlayerEconomy::GetPlayerEconList()
{
	return pEconList;
}
