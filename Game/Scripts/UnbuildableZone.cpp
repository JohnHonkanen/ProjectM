/*
UnbildableZone class used to block the placement of other buildings
*/
#include "LightCycle.h"
#include "UnbuildableZone.h"
#include "components\MeshRenderer.h"
using namespace std;

UnbuildableZone::UnbuildableZone() {
}

UnbuildableZone::~UnbuildableZone()
{
}

UnbuildableZone::UnbuildableZone(string buildingName, bool placed)
{
	name = buildingName;
	isPlaced = placed;
}

UnbuildableZone * UnbuildableZone::Create(string name, bool placed)
{
	UnbuildableZone *w = new UnbuildableZone(name, placed);
	w->structureType = WAREHOUSE;
	return w;
}

UnbuildableZone * UnbuildableZone::Create(GameObject* gameObject, GameManager* gameManager)
{
	UnbuildableZone *uz = new UnbuildableZone();
	MeshRenderer::Create(gameObject, "Game/Assets/Models/rock/Rock.obj", DEFERRED);
	uz->tileWidth = 3;
	uz->structureType = UNBUILDABLEZONE;
	return uz;
}

void UnbuildableZone::Copy(GameObject *copyObject)
{
	UnbuildableZone * copy = new UnbuildableZone();
	copy->structureType = UNBUILDABLEZONE;
	copy->tileWidth = tileWidth;
	LightCycle::Create(copyObject);
	copyObject->AddComponent(copy);
}

void UnbuildableZone::OnLoad()
{
}

void UnbuildableZone::Update()
{
}



