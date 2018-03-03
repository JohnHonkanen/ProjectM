#include "Billboard.h"
#include "components\Camera.h"
#include <GL\glew.h>
#include "hud\HUDQuad.h"
#include "render\OGLShader.h"
#include "core\GameEngine.h"
#include "glm\gtc\type_ptr.hpp"
#include <glm\gtc\matrix_transform.hpp>


unsigned int Billboard::VAO = 0;	// static field is initialised
unsigned int Billboard::VBO = 0;	// static field is initialised

Billboard * Billboard::Create(GameObject * gameobject, std::string texture)
{
	Billboard * bb = new Billboard();
	bb->texture = texture;

	gameobject->AddComponent(bb);

	return bb;
}

void Billboard::Copy(GameObject * copyObject)
{
	//To Be filled
}

void Billboard::OnLoad()
{
	quad.SetupQuad();
}

void Billboard::Start()
{
	camera = Camera::mainCamera;
	shader = GameEngine::manager.shaderManager.GetShaderProgram("billboard"); //Need to Create new Shader for Billboarding
}

void Billboard::Update(double dt)
{
}

void Billboard::Draw()
{
	shader->Use();
	glm::mat4 model, view, projection;

	CalculateModelMatrix();
	model = transform->GetLocalToWorldMatrix();
	view = camera->GetViewMatrix();
	projection = camera->GetProjectionMatrix();

	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3f(glGetUniformLocation(shader->program, "cameraRight_worldspace"), view[0][0], view[1][0], view[2][0]);
	glUniform3f(glGetUniformLocation(shader->program, "cameraUp_worldspace"), view[0][1], view[1][1], view[2][1]);

	glm::vec3 pos = transform->GetPosition();
	glUniform3f(glGetUniformLocation(shader->program, "billboardPos"), pos.x ,pos.y, pos.z); // The billboard will be just above the cube
	glUniform2f(glGetUniformLocation(shader->program, "billboardSize"), 10.0f, 10.0f);     // and 1m*12cm, because it matches its 256*32 resolution =)



	if (!texture.empty()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(texture));
		glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);
	}

	quad.Draw();
}

void Billboard::CalculateModelMatrix()
{
	
	
}

