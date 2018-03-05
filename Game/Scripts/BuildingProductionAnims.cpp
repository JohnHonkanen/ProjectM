#include "BuildingProductionAnims.h"
#include "core\GameObject.h"
#include "Billboard.h"
BuildingProductionAnims::~BuildingProductionAnims()
{
	delete prefab;
}

BuildingProductionAnims * BuildingProductionAnims::Create(GameObject * gameobject)
{
	BuildingProductionAnims * bpa = new BuildingProductionAnims();
	
	gameobject->AddComponent(bpa);

	return bpa;
}

void BuildingProductionAnims::Copy(GameObject * copyObject)
{
}

void BuildingProductionAnims::OnLoad()
{
	//Set up prefab
	prefab = new GameObject("billboard_spawn");
	Billboard::Create(prefab, "Game/Assets/Textures/chicken-16.png");

	billboard = prefab->Instantiate();
	billboard->transform->Scale(vec3(1));
}

void BuildingProductionAnims::Start()
{
	spawnLocation = gameObject->transform.get();
	timer.SetDelay(1000);
	timer.StartClock();
}

void BuildingProductionAnims::Update(double dt)
{
	timer.UpdateClock();
	Billboard *billboardComponent = billboard->GetComponent<Billboard>();
	if (timer.Alarm())
	{
		billboard->transform->SetPosition(spawnLocation->GetPosition() + vec3(0,10,0));
		timer.ResetClock();
		billboardComponent->alpha = 1;
	}
	else {
		billboardComponent->alpha -= dt / 1000;
		billboard->transform->Translate(vec3(0, 25* dt/1000, 0));
	}
}

void BuildingProductionAnims::Spawn()
{
}
