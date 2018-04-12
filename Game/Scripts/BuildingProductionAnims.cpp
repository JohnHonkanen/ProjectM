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
	BuildingProductionAnims * bpa = Create(copyObject);
}

void BuildingProductionAnims::OnLoad()
{
	//Set up prefab
	prefab = new GameObject("billboard_spawn");
	Billboard::Create(prefab, texture);

	billboard = prefab->Instantiate();
	billboard->transform->Scale(vec3(1));

	billboard->GetComponent<Billboard>()->alpha = 0;
}

void BuildingProductionAnims::Start()
{
	spawnLocation = gameObject->transform.get();
}

void BuildingProductionAnims::Update(double dt)
{
	//Nothing to display
	if (texture.empty())
	{
		return;
	}

	Billboard *billboardComponent = billboard->GetComponent<Billboard>();


	if (billboardComponent->alpha >= 0)
	{
		billboardComponent->alpha -= dt / 1000;
		billboard->transform->Translate(vec3(0, 25 * dt / 1000, 0));
	}

	if (billboardComponent->alpha <= 0)
	{
		billboard->transform->SetPosition(vec3(0, -10, 0));
	}
		
}

void BuildingProductionAnims::SetTextureToDisplay(std::string texture)
{
	this->texture = texture;
	Billboard *billboardComponent = billboard->GetComponent<Billboard>();

	billboardComponent->SetTexture(texture);

}

void BuildingProductionAnims::Spawn()
{
	Billboard *billboardComponent = billboard->GetComponent<Billboard>();
	billboard->transform->SetPosition(spawnLocation->GetPosition() + vec3(0, 10, 0));
	billboardComponent->alpha = 1;
}

void BuildingProductionAnims::DestroyBillboard()
{
	billboard->Destroy();
}
