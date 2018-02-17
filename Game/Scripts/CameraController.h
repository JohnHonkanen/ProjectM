#pragma once
#include "components\Behaviour.h"
#include <glm\glm.hpp>
#include "cereal\cereal.hpp"
#include "cereal\types\polymorphic.hpp"

namespace Engine {
	class Camera;
}

class CameraController : public Behaviour
{
public:
	static CameraController* Create(GameObject *gameObject);
	void Copy(GameObject *copyObject);
	void Start();
	void Update(double dt);
	void Input();

	template<class Archive>
	void serialize(Archive & ar)
	{
	}

private:
	float sensitivity;
	float speed;
	float smoothing;
	glm::vec3 focusPoint;
	glm::vec3 movement;
	float distance;

};

using namespace Engine;


#include <cereal/archives/xml.hpp>
//Register camera as a derived class
CEREAL_REGISTER_TYPE(CameraController);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, CameraController);