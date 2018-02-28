/*
	Camera controller class used to control the gameobject that camera component is part of.
*/
#pragma once
#include "components\Behaviour.h"
#include <glm\glm.hpp>
#include "cereal\cereal.hpp"
#include "cereal\types\polymorphic.hpp"
#include "core\Transform.h"
#include "components\Camera.h"


class CameraController : public Behaviour
{
public:
	static CameraController* Create(GameObject *gameObject, Transform *focusPoint);
	void Copy(GameObject *copyObject);
	void Start();
	void Update(double dt);
	void Input();

	template<class Archive>
	void serialize(Archive & ar)
	{
	}

private:

	void CalculateAngleAroundPoint();

	Transform * focusPoint;
	Camera * camera;
	float sensitivity;
	float speed;
	float smoothing;
	float angleAroundPoint = 0.0f;
	glm::vec3 movement;
	float distance;

	float pitch = 50;
	float yaw = 0;
	vec3 front;

	const float zoomSpeed = 3.0f;
	const float pitchSpeed = 0.3f;
	const float angleRotationSpeed = 0.3f;
	const float lerpAmount = 0.1f;

};

using namespace Engine;


#include <cereal/archives/xml.hpp>
//Register camera as a derived class
CEREAL_REGISTER_TYPE(CameraController);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, CameraController);