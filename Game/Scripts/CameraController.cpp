#include "CameraController.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"
#include "components\Camera.h"
#include <glm\gtx\compatibility.hpp>

CameraController * CameraController::Create(GameObject * gameObject)
{
	CameraController *c = new CameraController();
	gameObject->AddComponent(c);

	return c;
}

void CameraController::Copy(GameObject * copyObject)
{
	CameraController *c = new CameraController();
	copyObject->AddComponent(c);
}

void CameraController::Start()
{
	distance = 200;
	sensitivity = 0.5f;
	speed = 1.0f;
	smoothing = 0.2f;

	transform->SetEulerAngle(vec3(60.0f, 0, 0));
	transform->SetPosition(vec3(0, distance, 0));
}

void CameraController::Update(double dt)
{
	vec3 smoothMovement;
	vec3 movementDir = movement * vec3(sensitivity * smoothing);
	movementDir *= speed;

	smoothMovement.x = -lerp(smoothMovement.x, movementDir.x, 1.0f/smoothing) * dt;
	smoothMovement.z = lerp(smoothMovement.z, movementDir.z, 1.0f / smoothing) * dt;

	transform->Translate(smoothMovement);

}

void CameraController::Input()
{
	InputManager * inputManager = &GameEngine::manager.inputManager;
	// Horizontal
	int h = inputManager->GetKey("Horizontal");

	// Vertical
	int v = inputManager->GetKey("Vertical");

	movement = vec3(h, 0, v);
}
