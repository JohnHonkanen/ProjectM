/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B000308927)
*/

#include "Warehouse.h"

using namespace std;

//needs create method

//copy method - see camera control

//serialization code please

string Warehouse::DisplayContents()
{
	for (int i = 0; i < storage.size; i++)
	{
		return storage[i];
	}
}

/*
Sends resource to another building
*/
void Warehouse::SendItem()
{
}
/*
Receives resource from another building and stores it in the warehouse storage
*/
void Warehouse::ReceiveItem()
{
}

/*
Checks the warehouse storage against the item to see if it has space for the item and whether it can store the item type.

@param - itemType - The type of resource to be sent to the Warehouse

@returns true if the itemType is acceptable to the Warehouse, false if not.
*/
bool Warehouse::CheckItem(string itemType)
{
	/*
	Checks the item type against a list of acceptable item types.
	*/
}

/*
If the CheckItem method succeeds then this method stores the resource it in the appropriate location in internal storage of the warehouse.

*/
void Warehouse::PlaceItem()
{
	/*
	Will read the storage array and place the item in the first empty slot.
	*/
}

void Warehouse::Update(int change)
{
	SetStorageSize(change);
}
