#pragma once

#include "MobaJuiceCore.h"
#include "Scripts\Resources.h"
#include "Scripts\ResourceManager.h"
#include "Scripts\PlayerEconomy.h"

int main(int argc, char *argv[])
{
	//GameEngine engine = GameEngine();
	////engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	//engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) +  "default-settings.xml").c_str());
	//Scene *scene = engine.CreateScene("BlankScene");
	//engine.Run();

	PlayerEconomy playerEconomy = PlayerEconomy();
	playerEconomy.Init();

	ResourceManager resourceManager = ResourceManager();
	
	Resources resource = resourceManager.AddResource(1, "item 1", "TEST", 100, 0);
	
	cout << "ResourceID: " << resource.GetItemID() << endl;
	cout << "Item Name: " << resource.GetName() << endl;
	cout << "Slug: " << resource.GetSKU() << endl;
	cout << "Cost: " << resource.GetBasePrice() << endl;
	cout << "Stock: " << resource.GetItemAmount() << endl << endl;

	resource = resourceManager.AddResource(2, "item 2", "TEST", 150, 0);


	cout << "ResourceID: " << resource.GetItemID() << endl;
	cout << "Item Name: " << resource.GetName() << endl;
	cout << "Slug: " << resource.GetSKU() << endl;
	cout << "Cost: " << resource.GetBasePrice() << endl;
	cout << "Stock: " << resource.GetItemAmount() << endl << endl;

	resource.SetItemAmount(1024);
	resource.SetItemPrice(5);

	cout << "ResourceID: " << resource.GetItemID() << endl;
	cout << "Item Name: " << resource.GetName() << endl;
	cout << "Slug: " << resource.GetSKU() << endl;
	cout << "Cost: " << resource.GetBasePrice() << endl;
	cout << "Stock: " << resource.GetItemAmount() << endl << endl;

	//resource.IncreaseItemPrice(5);

	//cout << "ResourceID: " << resource.GetItemID() << endl;
	//cout << "Item Name: " << resource.GetName() << endl;
	//cout << "Slug: " << resource.GetSKU() << endl;
	//cout << "Cost: " << resource.GetBasePrice() << endl;
	//cout << "Stock: " << resource.GetItemAmount() << endl << endl;

	//resource.SetItemPrice(10);
	//resource.DecreaseItemPrice(50);

	//cout << "ResourceID: " << resource.GetItemID() << endl;
	//cout << "Item Name: " << resource.GetName() << endl;
	//cout << "Slug: " << resource.GetSKU() << endl;
	//cout << "Cost: " << resource.GetBasePrice() << endl;
	//cout << "Stock: " << resource.GetItemAmount() << endl << endl;

	return 0;
}