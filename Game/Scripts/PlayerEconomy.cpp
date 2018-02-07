#include "PlayerEconomy.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::~PlayerEconomy()
{
}

void PlayerEconomy::GiveGoldBars(int amountToGive)
{
	this->resource.SetItemAmount(amountToGive);
}

void PlayerEconomy::AddGoldBars(int goldBars)
{
	this->goldBars += goldBars;
}

void PlayerEconomy::RemoveGoldBars(int goldBars)
{
	this->goldBars -= goldBars;
}

int PlayerEconomy::GetGBAmount(int GBAmount)
{
	return this->goldBars = GBAmount;
}

void PlayerEconomy::Init()
{
	PlayerEconomy playerEconomy = PlayerEconomy();
	ResourceManager resourceManager = ResourceManager();
	this->resource = resourceManager.AddResource(0, "Gold Bars", "GOLD", 1, 0); 
	
	cout << "Gold Bars: " << resource.GetItemID() << endl;
	playerEconomy.GiveGoldBars(1000);
	cout << "GB Amount: " << GetGBAmount(resource.GetItemAmount()) << endl << endl;
}
