#pragma once
#include "Resources.h"
#include <map>

class RecipeManager {
private:
	map<ResourceName, ResourceName> recipes;

public:
	void Add(ResourceName input, ResourceName ouput);
	ResourceName GetInput(ResourceName output);
	void OnLoad();
};