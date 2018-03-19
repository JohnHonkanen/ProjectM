#include "PlayerEconomy.h"
#include "PlayerEconManager.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::PlayerEconomy(ResourceManager* resourceManager, PlayerEconManager* playerEconManager)
{
	this->resourceManager = resourceManager;
	this->playerEconManager = playerEconManager;
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
	int amount = 0;
	this->resource.IncreaseItemAmount(goldBars);
	playerEconManager->HUBInventory->AddItem(ResourceName::Gold, goldBars);
	playerEconManager->HUBInventory->CheckStorageFull(ResourceName::Gold);
}

void PlayerEconomy::RemoveGoldBars(int goldBars)
{
	int temp = this->resource.GetItemAmount();
	temp -= goldBars;
	this->resource.ReduceItemAmount(temp);
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
	return this->resource.GetItemAmount();
}

Resources PlayerEconomy::GetResouce()
{
	return this->resource;
}

string PlayerEconomy::GetGBIcon()
{
	return this->resource.GetResourceIcon();
}
