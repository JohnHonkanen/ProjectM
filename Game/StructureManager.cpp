/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/

#include "StructureManager.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace Engine {
	StructureManager::StructureManager()
	{
	}
	StructureManager::~StructureManager()
	{
	}

	//original
	void StructureManager::CreateStructure(std::string request)
	{
		if (request == "Hub")
		{
			/*Structure *s = Create
			structure.insert(pair<string, Structure*>(name, s));*/
			// Not sure about these lines - Trying to create a Structure for the list.
		}

		if (request == "Factory")
		{
			
			string nextName = (request + " " + factoryCounter);
			factoryCounter++;
			Structure *object = new Structure(nextName);
			//RegisterStructure(object);

			return object;
		}

		if (request == "Warehouse")
		{
			
			string nextName = (request + " " + factoryCounter);
			warehouseCounter++;
			GameObject *object = new GameObject(nextName);
			//RegisterGameObject(object);

			return object;
		}

	}

	//void StructureManager::RegisterStructure(Structure * gameObject)
	//{
	//	if (gameObject->name == "") {
	//		int count = gameStructures.size();
	//		gameObject->name = "GameObject" + count;
	//	}
	//	//If already exist
	//	if (counter.count(gameObject->name) > 0) {
	//		string name = gameObject->name;
	//		gameObject->name = name + "_" + to_string(counter[name]);
	//		counter[name]++;
	//	}
	//	else {
	//		counter[gameObject->name] = 1;
	//	}


	//	gameStructures.insert(pair<string, StructureUniqPtr>(gameObject->name, StructureUniqPtr(gameObject)));
	//}

	//Structure * StructureManager::DeregisterStructure(std::string name)
	//{
	//	Structure * gameStructures = Find(name);
	//	gameStructures[name].release();
	//	gameStructures.erase(name);
	//	return gameStructures;
	//}

	///*
	//Creates a stucture from a list based on a string input and adds it to the object list.
	//
	//@param name - The name of the building on the list
	//*/


	//Structure * StructureManager::Find(std::string name)
	//{
	//	if (gameStructures.find(name) == gameStructures.end())
	//		return nullptr;

	//	return gameStructures[name].get();
	//}

	///*
	//Finds the font from a string input and creates a structure based on that.

	//@returns - Structure
	//*/
	//Structure * StructureManager::GetStructure(std::string name)
	//{
	//	auto it = structure.find(name);
	//	if (it != structure.end()) {
	//		return structure[name];
	//	}

	//	CreateStructure(name);
	//	return structure[name];
	//}

	//Structure * StructureManager::LoadPrefab(const char * prefab)
	//{
	//	StructureUniqPtr gameStructure;

	//	ifstream is(prefab);
	//	cereal::XMLInputArchive iArchive(is);
	//	iArchive(gameStructure);

	//	Structure * obj = gameStructure.get();
	//	gameStructure.release();
	//	RegisterStructure(obj);

	//	return obj;

	//}

	//bool StructureManager::SavePrefab(const char * prefab, std::string name)
	//{
	//	if (gameStructures.find(name) == gameStructures.end())
	//		return false;

	//	ofstream os(prefab);
	//	cereal::XMLOutputArchive oArchive(os);
	//	oArchive(gameStructures[name]);

	//	return true;
	//}
}