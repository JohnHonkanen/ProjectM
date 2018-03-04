#pragma once
#include "components\Behaviour.h"

namespace Engine
{
	class MeshRenderer;
}
class BuildinggSpawnAnim : public Behaviour
{
public:
	static BuildinggSpawnAnim * Create(GameObject* gameobject);
	void Copy(GameObject *copyObject);
	void Start();
	void Update(double dt);
private:
	MeshRenderer * renderer;
};