#pragma once
#include "components\Behaviour.h"
#include "hud\HUDQuad.h"
#include <glm\glm.hpp>
namespace Engine {
	class OGLShader;
	class Camera;

}
class Billboard : public Behaviour
{
public:
	static Billboard * Create(GameObject* gameobject, std::string texture);
	void Copy(GameObject *copyObject);
	void OnLoad();
	void Start();
	void Update(double dt);
	void Draw();

	/** Sets the texture of the billboard particle image*/
	void SetTexture(std::string texture);

	static unsigned int VAO, VBO;

	float alpha;
private:
	std::string texture;
	void CalculateModelMatrix();
	OGLShader * shader;
	Engine::HUD::HUDQuad quad;
	Camera *camera;

};