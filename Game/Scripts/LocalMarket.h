#pragma once
#include "ResourceManager.h"
#include "core\GameObject.h"
#include "utility\Clock.h"

class LocalMarket {
public:
	LocalMarket();
	LocalMarket(ResourceManager* resourceManager);
	~LocalMarket();

	int GetCurrentPrice(ResourceName resourceName);
	void SetNewCurrentPrice(ResourceName resourceName;

	int GetModifier();
	void SetModifier();

	void OnLoad();
	void Start();
	void Update();


private:
	Engine::Utility::Clock clock;
	ResourceManager* resourceManager;

	int modifier = 1;
};