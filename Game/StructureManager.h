/*
The Structure Manager class used to create and manage structures
Dev: Jack Smith (B000308927)
*/
#pragma once
#include <map>
#include <memory>
#include "Structure.h"

using namespace std;
namespace Engine {

	class StructureManager {
	public:
		StructureManager();							// Deafult constructor
		~StructureManager();						// Deafult destructor
		Structure * GetStructure(std::string name);		// Structure accessor

	private:
		void CreateStructure(std::string name);		// Creates a new structure using a file name input
		map<string, Structure*> structure;			// map struct used to store a structure related to a specific structure name from a file
	};
}

