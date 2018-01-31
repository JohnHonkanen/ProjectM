#pragma once

#include "components\Behaviour.h"
#include "components\TerrainSnapper.h"

using namespace Engine;

class ObjectPlacer : public Behaviour {
public:
	static ObjectPlacer * Create(GameObject *gameObject, GameObject * itemToBuild, TerrainSnapper  * snapper);
	void Copy(GameObject *copy) { assert(0); /*Cannot be copied*/ };

	void Update();
private:
	ObjectPlacer() {};

	bool buildOnce = true;
	GameObject * itemToBuild;
	TerrainSnapper * snapper;
};