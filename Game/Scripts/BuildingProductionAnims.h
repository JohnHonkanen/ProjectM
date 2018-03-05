#pragma once
#include "components\Behaviour.h"

class BuildingProductionAnims : public Behaviour
{
public:
	~BuildingProductionAnims();
	static BuildingProductionAnims * Create(GameObject* gameobject);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update(double dt);

	void SetTextureToDisplay(std::string texture);
	void Spawn();
private:
	
	Transform * spawnLocation;
	GameObject * billboard;
	GameObject * prefab;

	std::string texture;
};