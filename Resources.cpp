#include "Resources.h"



Resources::Resources()
{
}


Resources::~Resources()
{
}

void Resources::CreateItem(int itemID, string itemName, int itemValue, int itemQuality)
{
	itemID = this->itemID;
	itemName = this->itemName;
	itemValue = this->itemValue;
	itemQuality = this->itemQuality;
}

int Resources::GetItemID(int itemID)
{
	return itemID;
}

string Resources::GetItemName(string itemName)
{
	return itemName;
}

int Resources::SetItemValue(int itemID, int itemValue, float mood)
{
	int multiplier;
	mood = multiplier * GetItemValue(itemID, itemValue, mood);
	itemValue = itemValue * mood;

	return itemValue;
}

// Need to identify itemID
int Resources::GetItemValue(int itemID, int itemValue, float mood)
{
	return itemValue;
}

int Resources::SetItemQuality(int itemID, int itemQuality)
{
	int multiplier;
	mood = multiplier * GetItemQuality(itemID, itemValue);
	itemValue = itemValue * mood;

	return itemQuality;
}

int Resources::GetItemQuality(int itemID, int itemQuality)
{
	itemQuality = 1;
	return itemQuality;
}
