#include "Resources.h"
#include "core\GameEngine.h"

using namespace Engine;

Resources::Resources()
{
}

Resources::Resources(ResourceName itemID, string itemName, string sku, int basePrice, int itemStock, string resourceIcon, int stackLimit)
{
	this->itemID = static_cast<int>(itemID);
	this->itemName = itemName;
	this->sku = sku;
	this->basePrice = basePrice;
	this->itemStock = itemStock;
	this->resourceIcon = resourceIcon;
	this->resourceName = itemID;
	this->stackLimit = stackLimit;
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
int Resources::GetItemID() const
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
	this->itemStock = itemStock;
}

/*Increase Item price*/
void Resources::IncreaseItemPrice(float modifier)
{
	mood = modifier;

	this->basePrice += GetBasePrice() + baseModifier * mood;
}

/*Increase Item price*/
void Resources::DecreaseItemPrice(float modifier)
{
	mood = modifier;

	this->basePrice -= mood;

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

void Resources::SetStackLimit(int stackLimit)
{
	this->stackLimit = stackLimit;
}

int Resources::GetStackLimit() const
{
	return this->stackLimit;
}

void Resources::update()
{
	int IOKey = GameEngine::manager.inputManager.GetKey("IO");
	int oldPrice = basePrice;
	
	if (IOKey == 1) {
		if (keyReleased == true) { // if key I is pressed (Increase)
			keyReleased = false;
			IncreaseItemPrice(2.5);
			cout << "itemPrice increased from: " << oldPrice << " to " << basePrice << endl;
		}
	}
	else {
		if (IOKey == 0) {
			keyReleased = true;
		}
	}

	if (IOKey == -1) { // Needs optimization
		if (keyReleased == true) { // if key I is pressed (Increase)
			keyReleased = false;
			DecreaseItemPrice(2.5);
			cout << "itemPrice decreased from: " << oldPrice << " to " << basePrice << endl;
		}
	}
	else {
		if (IOKey == 0) {
			keyReleased = true;
		}
	}
}

string Resources::GetResourceIcon()
{
	return this->resourceIcon;
}

void Resources::SetResourceIcon(string resourceIcon)
{
	this->resourceIcon = resourceIcon;
}

ResourceName Resources::GetResouceID()
{
	return this->resourceName;
}


