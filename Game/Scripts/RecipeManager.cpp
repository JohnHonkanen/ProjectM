#include "RecipeManager.h"

void RecipeManager::Add(ResourceName input, ResourceName ouput)
{
	recipes[ouput] = input;
}

ResourceName RecipeManager::GetInput(ResourceName output)
{//check if key exists
	auto it = recipes.find(output);
	if (it != recipes.end()) {
		return recipes[output];
	}
	return ResourceName::Null_Resource;
}

void RecipeManager::OnLoad()
{
	Add(ResourceName::SpaceCow, ResourceName::SpaceCow_Beef);
	Add(ResourceName::SpaceCow_Milk, ResourceName::SpaceCow_Cheese);
}
