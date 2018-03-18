#pragma once
#include "ResourceManager.h"
#include "core\GameObject.h"
#include "utility\Clock.h"

class LocalMarket {
public:
	LocalMarket();
	LocalMarket(ResourceManager* resourceManager);
	~LocalMarket();

	void OnLoad();
	void Start();
	void Update();


private:
	Engine::Utility::Clock clock;
	ResourceManager* resourceManager;
};