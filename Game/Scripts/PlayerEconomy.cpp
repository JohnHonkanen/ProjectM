#include "PlayerEconomy.h"

PlayerEconomy::PlayerEconomy()
{
}

PlayerEconomy::~PlayerEconomy()
{
}

int PlayerEconomy::GiveGoldBars()
{
	return this->goldBars;
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
	Resources resource0 = Resources(0, "Gold Bars", "GOLD", 1, 0);
	ResourceManager resourceManager = ResourceManager();

	
	resource0 = resourceManager.AddResource(resource0, resource0.GetItemID());
	cout << "Gold Bars: " << resource0.GetItemID() << endl;
	cout << "GB Amount: " << GetGBAmount(resource0.GetItemAmount()) << endl;
}
