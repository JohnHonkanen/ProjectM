#pragma once
#include "LocalMarket.h"
#include "ResourceManager.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "utility\Clock.h"
#include <string>
#include <vector>
#include <iostream>

#define LOCAL 0
#define GALACTIC 1

using namespace std;
class MarketManager : public Behaviour {
public:
	MarketManager();
	~MarketManager();

	LocalMarket AddMarket(MarketName marketname, string nameOfMarket);
	LocalMarket Find(MarketName marketName);

	static MarketManager* Create(GameObject* gameObject);

	void SetResourceManager(ResourceManager* resourceManager);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update();
	
	vector <LocalMarket*> GetList() const;
private:
	ResourceManager* resourceManager;
	vector <LocalMarket> marketQueue;
	Engine::Utility::Clock clock;

	int marketID;

};