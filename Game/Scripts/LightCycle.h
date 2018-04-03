#pragma once
#include "components\Behaviour.h"
#include "components\Light.h"
#include "GameManager.h"
class LightCycle : public Behaviour
{
public:
	static LightCycle *Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Update(double dt);

	void ActivateLight();
private:
	Light * light;
	GameObject *lightGameObject;
};