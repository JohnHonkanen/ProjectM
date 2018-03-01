#include "CameraController.h"
#include "core\GameEngine.h"
#include "core\InputManager.h"
#include <glm\gtx\compatibility.hpp>
#include <glm\gtc\matrix_transform.hpp>

CameraController * CameraController::Create(GameObject * gameObject, Transform *focusPoint)
{
	CameraController *c = new CameraController();
	c->focusPoint = focusPoint;

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
	//Add Keys Q and E
	Engine::GameEngine::manager.inputManager.AddKey("Rotate", "e", "q");
	Engine::GameEngine::manager.inputManager.AddKey("Zoom", "f", "v");
	Engine::GameEngine::manager.inputManager.AddKey("Reset", "r");
	/** Default values */
	distance = 200; //Distance from the ground
	sensitivity = 0.5f; //Sensitivity of keypress
	speed = 1.0f;
	smoothing = 0.2f; //Smoothing factor for lerp

	/** Default Setup */
	transform->SetEulerAngle(vec3(90, 0, 0));
	transform->SetPosition(vec3(0, distance, -50));

	/*Disable Camera view Calc*/
	camera = Camera::mainCamera;
	camera->customViewMatrix = true;

	angleAroundPoint = 10.0f;
}

float r = 1.0f;
void CameraController::Update(double dt)
{
	CalculateAngleAroundPoint();
	/** Calculate the smooth movement to translate by*/
	vec3 smoothMovement;
	vec3 movementDir = movement * vec3(sensitivity * smoothing);
	movementDir *= speed;
	smoothMovement.x = lerp(smoothMovement.x, movementDir.x, 1.0f/smoothing) * dt;
	smoothMovement.z = lerp(smoothMovement.z, movementDir.z, 1.0f / smoothing) * dt;

	
	focusPoint->Translate(smoothMovement);

	//Set a custom View matrix
	mat4 view = lookAt(transform->GetPosition(), focusPoint->GetPosition(), vec3(0,1,0));
	camera->SetViewMatrix(view);

	vec3 focusPointRot = focusPoint->GetRotation();
	float theta = radians(focusPointRot.y);

	float offsetX = -100 * sin(theta);
	float offsetZ = -100 * cos(theta);

	transform->SetPosition(vec3(offsetX, distance, offsetZ));

	int key = GameEngine::manager.inputManager.GetKey("Rotate");
	focusPoint->Rotate(vec3(0, key, 0));

}

void CameraController::Input()
{
	/** Check and poll key inputs */
	InputManager * inputManager = &GameEngine::manager.inputManager;
	// Horizontal
	int h = inputManager->GetKey("Horizontal");

	// Vertical
	int v = inputManager->GetKey("Vertical");

	vec3 front = focusPoint->Front();
	vec3 right = focusPoint->Right();
	vec3 hDir = -right * (float)h;
	vec3 vDir = front * (float)v;
	movement = hDir + vDir;

	int key = GameEngine::manager.inputManager.GetKey("Reset");
	if (key == 1)
	{
		focusPoint->SetEulerAngle(vec3(0));
	}

	key = GameEngine::manager.inputManager.GetKey("Zoom");
	if (key > 0)
	{
		distance -= 1.0f;
	}
	else if (key < 0)
	{
		distance += 1.0f;
	}
}

void CameraController::CalculateAngleAroundPoint()
{
	angleAroundPoint = (1.0f - lerpAmount) * angleAroundPoint + lerpAmount * focusPoint->GetRotation().y;
}
