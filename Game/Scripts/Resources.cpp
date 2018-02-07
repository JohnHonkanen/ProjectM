#include "Resources.h"

Resources::Resources()
{
}

Resources::Resources(int itemID, string itemName, string sku, int basePrice, int itemStock)
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

/*Increment Item Stock in marketplace*/
void Resources::IncreaseItemAmount(int itemStock)
{
	this->itemStock += itemStock;
}

/*Decrement Item Stock in marketplace*/
void Resources::ReduceItemAmount(int itemStock)
{
	this->itemStock -= itemStock;
}

/*Set Item Stock in marketplace*/
void Resources::SetItemAmount(int itemStock)
{
	this->itemStock += itemStock;
}

/*Increase Item price*/
void Resources::IncreaseItemPrice(float modifier)
{
	mood = modifier;

	this->basePrice += GetBasePrice() * mood;
}

/*Increase Item price*/
void Resources::DecreaseItemPrice(float modifier)
{
	mood = modifier;

	this->basePrice -= GetBasePrice() * mood;

	if (this->basePrice < 0) {
		SetItemPrice(1);
	}
}

void Resources::SetItemPrice(int basePrice)
{
	this->basePrice = basePrice;
}

void Resources::SetItemName(string itemName)
{
	this->itemName = itemName;
}

void Resources::SetItemSKU(string itemSKU)
{
	this->sku = itemSKU;
}

void Resources::SetItemID(int itemID)
{
	this->itemID = itemID;
}

void Resources::update()
{
	if()
}


