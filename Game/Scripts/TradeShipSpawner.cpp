#include "TradeShipSpawner.h"
#include "core\GameObject.h"
#include "components\MeshRenderer.h"

TradeShip * TradeShip::Create(GameObject * gameObject)
{
	TradeShip *ts = new TradeShip();

	gameObject->AddComponent(ts);
	MeshRenderer::Create(gameObject, "Game/Assets/Models/mobajuice/Trader.dae");
	gameObject->material->diffuseMap = "";
	return ts;
}

//End Of TradeShip Section

TradeShipSpawner::~TradeShipSpawner()
{
	delete prefab->gameObject;
}
void TradeShipSpawner::OnLoad()
{
	GameObject * gameObject = new GameObject("TradeShipPrefab");
	prefab = TradeShip::Create(gameObject);
}


