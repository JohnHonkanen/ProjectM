#pragma once

#include "components\Behaviour.h"
#include "core\GameObject.h"

class Contract : public Behaviour{
public:
	Contract();
	~Contract();

	static Contract* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Update();

	void Start();


private:


};