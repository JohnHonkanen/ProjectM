#include "BuildingSpawnAnim.h"
#include "core\GameObject.h"
#include "components\MeshRenderer.h"
BuildinggSpawnAnim * BuildinggSpawnAnim::Create(GameObject * gameobject)
{
	BuildinggSpawnAnim * bsa = new BuildinggSpawnAnim();
	gameobject->AddComponent(bsa);

	return bsa;
}

void BuildinggSpawnAnim::Copy(GameObject * copyObject)
{
	Create(copyObject);
}

void BuildinggSpawnAnim::Start()
{
	renderer = gameObject->GetComponent<MeshRenderer>();
	renderer->partialRenderValue = 0;
}

void BuildinggSpawnAnim::Update(double dt)
{
	if (renderer->partialRenderValue < 100)
	{
		renderer->partialRenderValue += dt / 1000.0f;
	}
}
