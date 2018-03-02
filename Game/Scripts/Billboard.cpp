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

void Billboard::OnLoad()
{
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

	if (!texture.empty()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GameEngine::manager.textureManager.getTexture(texture));
		glUniform1i(glGetUniformLocation(shader->program, "texture0"), 0);
	}

	quad.Draw();
}

void Billboard::CalculateModelMatrix()
{
	vec3 lookAt, billboardToCamProj, billboardToCam, upAux;
	mat4 modelView;
	float angleCosine;

	vec3 camaraPos = camera->transform->GetPosition();
	vec3 billBoardPos = transform->GetPosition();

	billboardToCamProj = camaraPos - billBoardPos;
	billboardToCamProj.y = 0;

	//Original LookAt
	lookAt = vec3(0,0,1);

	billboardToCamProj = normalize(billboardToCamProj);

	upAux = cross(lookAt, billboardToCamProj);

	angleCosine = (lookAt.x * billboardToCamProj.x) + (lookAt.y * billboardToCamProj.y) + (lookAt.z * billboardToCamProj.z);

	mat4 rotation = mat4(1);
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
	{
		//Rotate
		rotation = glm::rotate(rotation, (float)(angleCosine * 180 / 3.14), upAux);
	}

	billboardToCam = camaraPos - billBoardPos;

	angleCosine = (billboardToCam.x * billboardToCamProj.x) + (billboardToCam.y * billboardToCamProj.y) + (billboardToCam.z * billboardToCamProj.z);

	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
	{
		if (billboardToCam.x < 0)
		{
			rotation = glm::rotate(rotation, (float)(angleCosine * 180 / 3.14), vec3(1,0,0));
		}
		else 
		{
			rotation = glm::rotate(rotation, (float)(angleCosine * 180 / 3.14), vec3(-1, 0, 0));
		}
	}

	transform->SetQuaternion(quat(rotation));
	
}

