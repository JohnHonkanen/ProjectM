#include "PlayerEconomy.h"
#include "PlayerEconManager.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::PlayerEconomy(ResourceManager* resourceManager, PlayerEconManager* playerEconManager)
{
	this->resource = resourceManager->FindResource(0);
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
	this->resource.IncreaseItemAmount(goldBars);
	StoreGold(this->resource);
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

void PlayerEconomy::StoreGold(Resources resourceToStore)
{
	inventory.PlaceItem(resourceToStore);
}
