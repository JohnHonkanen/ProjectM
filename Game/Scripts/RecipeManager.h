#pragma once
#include "Resources.h"
#include <map>

class RecipeManager {
private:
	map<ResourceName, ResourceName> recipes;

public:

	void OnLoad();												//Generates a map of pairs, representing an ingredient and an output
	void Add(ResourceName input, ResourceName ouput);			//Method to add recipies to the map
	ResourceName GetInput(ResourceName output);					//Method used by other classes to find the required input for the players selected output
};