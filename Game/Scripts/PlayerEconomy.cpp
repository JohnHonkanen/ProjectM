#include "PlayerEconomy.h"
#include "PlayerEconManager.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::PlayerEconomy(Resources resource, PlayerEconManager* playerEconManager)
{
	this->resource = resource;
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
	//int currentGB = GetGBAmount();
	
}

void PlayerEconomy::RemoveGoldBars(int goldBars)
{
	this->goldBars -= goldBars;
}

int PlayerEconomy::SetGBAmount(int GBAmount)
{
	return this->goldBars = GBAmount;
}

int PlayerEconomy::GetGBAmount()
{
	return this->goldBars;
}

Resources PlayerEconomy::GetResouce()
{
	
	return this->resource;
}

string PlayerEconomy::GetGBIcon()
{
	return this->resource.GetResourceIcon();
}
