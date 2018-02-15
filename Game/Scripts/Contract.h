#pragma once

#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "ResourceManager.h"

class Contract : public Behaviour{
public:
	Contract();
	Contract(Resources resource, int paymentToRecieve, int amountToFulfill, int contractTime, int currentFullFilled);
	~Contract();

	static Contract* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();

	void Start();

private:
	int payment, amount, time;
	int current = 0;
	Resources Resource;

	bool active = false;
	bool complete = false;
};