#include "LightCycle.h"
#include "core\GameEngine.h"
#include "GameManager.h"
#include "glm\glm.hpp"
#include "glm\gtx\compatibility.hpp"
LightCycle * LightCycle::Create(GameObject * gameObject)
{
	LightCycle * lc = new LightCycle();
	

	gameObject->AddComponent(lc);

	return lc;
}

void LightCycle::Copy(GameObject * copyObject)
{
}

void LightCycle::OnLoad()
{
}

void LightCycle::Update(double dt)
{
	if (lightGameObject == nullptr)
	{
		return;
	}

	lightGameObject->transform->SetPosition(gameObject->transform->GetPosition() + vec3(0,30,0));
	LightProperties pointProp;
	if (GameManager::gameManager->dayNightCycle.GetTime() == TIME::NIGHT)
	{
		pointProp.ambient = lerp(pointProp.ambient, vec3(0.7f), 0.1f *float(dt / 1000));
		pointProp.diffuse = pointProp.ambient;
	}
	else {
		pointProp.ambient = lerp(pointProp.ambient, vec3(0.1f), 0.1f *float(dt / 1000));
		pointProp.diffuse = pointProp.ambient;
	}

	light->SetLightProperties(pointProp);
}

void LightCycle::ActivateLight()
{
	lightGameObject = GameEngine::manager.gameObjectManager->CreateGameObject("pointLight");
	light = Light::Create(lightGameObject, POINT_LIGHT);
	LightProperties pointProp = {
		POINT_LIGHT,
		vec3(0.0f),
		vec3(0.0f),
		vec3(0.15f),

		1.0f, 0.022f, 0.0019f
	};
	light->SetLightProperties(pointProp);
	lightGameObject->transform->SetPosition(gameObject->transform->GetPosition() + vec3(0, 30, 0));
}
