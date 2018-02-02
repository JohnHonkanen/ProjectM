/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/
#pragma once
#include <map>
#include <memory>
#include <cereal\cereal.hpp>
#include <cereal\types\map.hpp>
#include "Structure.h"

using namespace std;
namespace Engine {
	typedef std::unique_ptr<GameObject> StructureUniqPtr;


	class StructureManager {
	public:
		StructureManager();							// Deafult constructor
		~StructureManager();						// Deafult destructor

													/*
													Calls on Loading the GameEngine
													*/
		void OnLoad();
		/*
		Called after loading all objects
		*/
		void Start();
		/*
		Calls on the Input Loop before Update;
		*/
		void Input();
		/*
		Calls the update functions for all GameObjects in the manager
		*/
		void Update();
		/*
		Calls the draw functions for all GameObjects in the manager
		*/
		void Draw();

		///*
		//Registers and gives ownership of the gameObject to the Manager
		//@param gameObject	GameObject that gives the ownership
		//*/
		//void RegisterStructure(Structure * gameObject);
		///*
		//Deregister the GameObject with this name, and release ownership
		//@param name		Name of the gameObject
		//@return			Return the gameObject released. (Needs to be deleted somewhere)
		//*/
		//Structure * DeregisterStructure(std::string name);
		///*
		//Find the GameObject with this name
		//@param name	Name of the gameObject
		//*/
		//Structure * Find(std::string name);
		///*
		//Load the prefab via xml file
		//@param	prefab	Prefab xml file to be loaded
		//*/
		//GameObject *LoadPrefab(const char *prefab);
		//bool SavePrefab(const char *prefab, std::string name);

		//Structure * GetStructure(std::string name);		// Structure accessor

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(gameStructures));
		}
	private:
		void CreateStructure(std::string name);		// Creates a new structure using a file name input
		map<string, Structure*> structure;			// map struct used to store a structure related to a specific structure name from a file : original
		//map<string, StructureUniqPtr> gameStructures;
		//map<string, int> counter;
		int domeCounter;
		int factoryCounter;
		int warehouseCounter;


	};
}

