#pragma once
#include "components\Behaviour.h"
#include "utility\Clock.h"

class BuildingProductionAnims : public Behaviour
{
public:
	~BuildingProductionAnims();
	static BuildingProductionAnims * Create(GameObject* gameobject);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update(double dt);
private:
	void Spawn();
	Transform * spawnLocation;
	GameObject * billboard;
	GameObject * prefab;
	Engine::Utility::Clock timer;
};