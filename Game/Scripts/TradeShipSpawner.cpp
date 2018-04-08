#include "TradeShipSpawner.h"
#include "core\GameObject.h"
#include "components\MeshRenderer.h"
#include <glm\gtc\random.hpp>

TradeShip * TradeShip::Create(GameObject * gameObject)
{
	TradeShip *ts = new TradeShip();
	ts->dock = nullptr;
	gameObject->AddComponent(ts);
	MeshRenderer::Create(gameObject, "Game/Assets/Models/mobajuice/Trader.dae");
	gameObject->material->diffuseMap = "Game/Assets/Textures/building_selected.jpg";
	return ts;
}

void TradeShip::Copy(GameObject * gameObject)
{
	TradeShip *ts = new TradeShip();
	ts->dock = nullptr;
	gameObject->AddComponent(ts);
}

void TradeShip::SetDock(Dock * in_dock)
{
	dock = in_dock;
}

void TradeShip::Update(double dt)
{
	if (returning)
	{
		if (currentSpeed < 300.0f)
		{
			currentSpeed += 100.0f * dt / 1000;
		}
		rotYOffset = 0;
		MoveTo(cameFrom, dt);
		return;
	}
	vec3 dockPos = dock->transform->GetPosition();

	dockPos.y += 2.0f;

	MoveTo(dockPos, dt);
}

void TradeShip::Return()
{
	returning = true;
	landed = false;
}

void TradeShip::SetCameFrom(vec3 from)
{
	cameFrom = from;
}

void TradeShip::RotateToFace(vec3 pos)
{
	vec3 dir = pos - transform->GetPosition();
	float angle = atan2(dir.x, dir.z);
	vec3 objAngle = transform->GetRotation();
	objAngle.y = degrees(angle) + 90.0f + rotYOffset;
	transform->SetEulerAngle(objAngle);
}

void TradeShip::MoveTo(vec3 pos, double dt)
{
	float dist = distance(transform->GetPosition(), pos);
	if (dist < 50.0f)
	{
		if (currentSpeed > 10.0f)
		{
			currentSpeed -= 100.0f * dt / 1000.0f;
		}

		if (currentSpeed < 10.0f)
		{
			currentSpeed = 10.0f;
		}

		vec3 objAngle = transform->GetRotation();
		int rotY = int(objAngle.y) % 360;
		if (rotY < 90)
		{
			rotYOffset += 10 * dt / 1000.0f;
		}

	}
	if (dist > 1.0f && !landed)
	{
		RotateToFace(pos);
		vec3 dir = pos - transform->GetPosition();
		dir = normalize(dir);

		transform->Translate(dir * float(dt / 1000.0f) * currentSpeed);

		if (dist <= 2.0f)
		{
			if (!returning)
			{
				landed = true;
				dock->DockShip(this);
			}
			else {
				gameObject->Destroy();
			}

		}
	}
	else {
		vec3 objAngle = transform->GetRotation();
		int rotY = int(objAngle.y) % 360;

		if (rotY < 85 || rotY > 95)
		{
			transform->Rotate(vec3(0, 20 * dt / 1000.0f, 0));
		}
	}
}

//End Of TradeShip Section

TradeShipSpawner * TradeShipSpawner::Create(GameObject * gameObject)
{
	TradeShipSpawner * tss = new TradeShipSpawner();

	gameObject->AddComponent(tss);

	return tss;
}

TradeShipSpawner::~TradeShipSpawner()
{
	delete prefab->gameObject;
}
void TradeShipSpawner::Copy(GameObject * gameObject)
{
}
void TradeShipSpawner::OnLoad()
{
	GameObject * gameObject = new GameObject("TradeShipPrefab");
	prefab = TradeShip::Create(gameObject);
}

void TradeShipSpawner::Update()
{
}

void TradeShipSpawner::CreateTradeShip(Dock *dock)
{
	GameObject * gameObject = prefab->gameObject->Instantiate();
	TradeShip * ts = gameObject->GetComponent<TradeShip>();
	ts->transform->SetPosition(vec3(glm::linearRand(-1000, 1000), 500, glm::linearRand(-1000, 1000)));
	ts->SetCameFrom(ts->transform->GetPosition());
	ts->SetDock(dock);
	ts->transform->SetScale(vec3(20));
	ts->transform->Rotate(vec3(-90, 0, 0));
	tradeShips.push_back(ts);

}


