#pragma once
#include "components\Behaviour.h"
#include <glm\glm.hpp>
class Drone : public Behaviour
{
public:
	static Drone *Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);

	void Start();
	void Update(double dt);

	void SetDestination(vec3 destination);
private:
	float speed;
	float verticalSpeed;
	float acceleration;
	glm::vec3 destination;
	float minY;
	bool reachedDestination;
	bool liftOff;

};