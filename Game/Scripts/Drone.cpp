#include "Drone.h"
#include "core\GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
Drone * Drone::Create(GameObject * gameObject)
{
	Drone *d = new Drone();
	gameObject->AddComponent(d);

	return d;
}

void Drone::Copy(GameObject * copyObject)
{
	Drone *d = new Drone();
	d->destination = destination;
	copyObject->AddComponent(d);
}

void Drone::Start()
{
	//Default values
	speed = 100.0f;
	verticalSpeed = 30.0f;
	minY = 50.0f;
	liftOff = false;
}

void Drone::Update(double dt)
{
	if (!liftOff)
	{
		if (transform->GetPosition().y < minY)
		{
			transform->Translate(dvec3(0, verticalSpeed, 0) * (dt/1000.0f));
		}
		else {
			liftOff = true;
		}
	}
	else
	{
		if (!reachedDestination)
		{
			vec3 adjustedDestination = vec3(destination.x, minY, destination.z);
			vec3 dir = adjustedDestination - transform->GetPosition();
			
			dir = normalize(dir);
			transform->LookAt(dir);
			transform->Translate(dvec3(dir * speed) * (dt / 1000.0f));

			if (distance(transform->GetPosition(), adjustedDestination) < 1.0f)
			{
				reachedDestination = true;
			}
		}
		else {
			if (transform->GetPosition().y > -10.0f)
			{
				transform->Translate(dvec3(0, -verticalSpeed, 0) * (dt / 1000.0f));
			}
			else
			{
				//Time for destruction
			}
		}

		

	}


}

void Drone::SetDestination(vec3 destination)
{
	Drone::destination = destination;
}
