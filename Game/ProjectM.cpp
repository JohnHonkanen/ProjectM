#pragma once

#include "MobaJuiceCore.h"
#include "Scripts\Resources.h"
#include "Scripts\ResourceManager.h"

int main(int argc, char *argv[])
{
	//GameEngine engine = GameEngine();
	////engine.SetDefaultPath(GameEngine::Paths::SETTINGS, "../GameEngine/MobaJuiceEngine/Engine/settings/");
	//engine.LoadSettings(string(engine.GetPath(GameEngine::Paths::SETTINGS) +  "default-settings.xml").c_str());
	//Scene *scene = engine.CreateScene("BlankScene");
	//engine.Run();

	//Resources resource1 = Resources(1, "testItem", "TEST", 100, 0);
	
	ResourceManager resourceManager = ResourceManager();

	resourceManager.Init();

	Resources resource1 = resourceManager.FindResource(0);

	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;
	
	resource1.SetItemAmount(1024);
	resource1.SetItemPrice(5);

	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	resource1.IncreaseItemPrice(5);

	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	resource1.SetItemPrice(10);
	resource1.DecreaseItemPrice(50);

	cout << "ResourceID: " << resource1.GetItemID() << endl;
	cout << "Item Name: " << resource1.GetName() << endl;
	cout << "Slug: " << resource1.GetSKU() << endl;
	cout << "Cost: " << resource1.GetBasePrice() << endl;
	cout << "Stock: " << resource1.GetItemAmount() << endl << endl;

	return 0;
}