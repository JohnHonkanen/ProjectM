/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/

#include "StructureManager.h"
#include <iostream>

using namespace std;

namespace Engine {
	StructureManager::StructureManager()
	{
	}
	StructureManager::~StructureManager()
	{
	}

	/*
	Creates a stucture from a list based on a string input and adds it to the object list.
	
	@param name - The name of the building on the list
	*/
	void StructureManager::CreateStructure(std::string name)
	{
		if (name == "Hub")
		{
			/*Structure *s = Create
			structure.insert(pair<string, Structure*>(name, s));*/
			// Not sure about these lines - Trying to create a Structure for the list.
		}

		if (name == "Production")
		{

		}

		if (name == "Warehouse")
		{

		}
		
	}

	/*
	Finds the font from a string input and creates a structure based on that.

	@returns - Structure
	*/
	Structure * StructureManager::GetStructure(std::string name)
	{
		auto it = structure.find(name);
		if (it != structure.end()) {
			return structure[name];
		}

		CreateStructure(name);
		return structure[name];
	}


}