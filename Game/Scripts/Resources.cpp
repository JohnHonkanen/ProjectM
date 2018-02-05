#include "Resources.h"



Resources::Resources()
{
}

Resources::Resources(int itemID, string itemName, string sku, int basePrice)
{
	this->itemID = itemID;
	this->itemName = itemName;
	this->sku = sku;
	this->basePrice = basePrice;
	this->itemStock = itemStock;


}


Resources::~Resources()
{
}

/*Retrieve the Resource Name*/
string Resources::GetName()
{
	return this->itemName;
}

/*Retrieve the Stock-keeping Unit (Slug)*/
string Resources::GetSKU()
{
	return this->sku;
}

/*Retrieve the Resource ID*/
int Resources::GetItemID()
{
	return this->itemID;
}

/*Retrieve the Amount (stock) of resources available in the marketplace*/
int Resources::GetItemAmount()
{
	return this->itemStock;
}

/*Retrieve the Base price of the resource*/
int Resources::GetBasePrice()
{
	return this->basePrice;
}


