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

Resources PlayerEconomy::GetResouce()
{
	
	return this->resource;
}

string PlayerEconomy::GetGBIcon()
{
	return this->resource.GetResourceIcon();
}

void PlayerEconomy::Init()
{
	PlayerEconomy playerEconomy = PlayerEconomy();
	
	cout << "Gold Bars: " << resource.GetItemID() << endl;
	playerEconomy.GiveGoldBars(1000);
	cout << "GB Amount: " << GetGBAmount(resource.GetItemAmount()) << endl << endl;
}
