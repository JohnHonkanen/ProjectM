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

	Resources resource1 = Resources(1, "item 1", "TEST", 100, 0);
	Resources resource2 = Resources(2, "item 2", "TEST", 150, 0);
	ResourceManager resourceManager = ResourceManager();


	//Resources resource1 = resourceManager.FindResource(1);

	resource1 = resourceManager.AddResource(resource1, resource1.GetItemID());
	resource2 = resourceManager.AddResource(resource2, resource2.GetItemID());
	
	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;
	
	resource1.SetItemAmount(1024);
	resource1.SetItemPrice(5);

	resource1 = resourceManager.FindResource(2);


	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	resource1.SetItemAmount(1024);
	resource1.SetItemPrice(5);

	//cout << "ResourceID: " << resource1.GetItemID() << endl;
	//cout << "Item Name: " << resource1.GetName() << endl;
	//cout << "Slug: " << resource1.GetSKU() << endl;
	//cout << "Cost: " << resource1.GetBasePrice() << endl;
	//cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	//resource1.IncreaseItemPrice(5);

	//cout << "ResourceID: " << resource1.GetItemID() << endl;
	//cout << "Item Name: " << resource1.GetName() << endl;
	//cout << "Slug: " << resource1.GetSKU() << endl;
	//cout << "Cost: " << resource1.GetBasePrice() << endl;
	//cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	//resource1.SetItemPrice(10);
	//resource1.DecreaseItemPrice(50);

	//cout << "ResourceID: " << resource1.GetItemID() << endl;
	//cout << "Item Name: " << resource1.GetName() << endl;
	//cout << "Slug: " << resource1.GetSKU() << endl;
	//cout << "Cost: " << resource1.GetBasePrice() << endl;
	//cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	return 0;
}