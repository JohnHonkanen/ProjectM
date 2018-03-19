#pragma once
#include "LocalMarket.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "utility\Clock.h"
#include <list>

class MarketManager : public Behaviour {
public:
	MarketManager();
	~MarketManager();

	LocalMarket AddMarket(MarketName marketname);
	LocalMarket* Find();

	static MarketManager* Create(GameObject* gameObject);

	void SetResourceManager(ResourceManager* resourceManager);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update();
	
	list <LocalMarket*> GetList() const;
private:
	LocalMarket localMarket;
	LocalMarket marketList[2]; // Number of markets
	ResourceManager* resourceManager;
	list <LocalMarket*> marketQueue;
	Engine::Utility::Clock clock;

	int marketID;

};