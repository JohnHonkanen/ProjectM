#include "../stdafx.h"

#include "ObjectPlacer.h"
#include "core\GameEngine.h"
ObjectPlacer * ObjectPlacer::Create(GameObject * gameObject, GameObject * itemToBuild, TerrainSnapper * snapper)
{
	ObjectPlacer *p = new ObjectPlacer();
	p->itemToBuild = itemToBuild;
	p->snapper = snapper;

	gameObject->AddComponent(p);
	return p;
}

void ObjectPlacer::Update()
{
	if (!buildOnce) {
		if (GameEngine::manager.inputManager.GetKey("build") == 1) {

			buildOnce = true;
			GameObject * go = itemToBuild->Instantiate();

			vec3 pos = go->transform->GetPosition();
			std::cout << "Creating "<< go->name << " at " << pos.x << "||" << pos.y << "||" << pos.z << std::endl;
		}
	}

	if (GameEngine::manager.inputManager.GetKey("build") == 0)
		buildOnce = false;
	
}
