#pragma once
#include "Structure.h"
#include "GameManager.h"
#include "ContractManager.h"
#include "task_system\Task.h"


class Dock : public Structure
{
public:
	static Dock * Create();
	void Copy(GameObject * copyObject);
	void Update();
private:
	ContractManager * contractManager;
	Contract *contract;
	v1::TaskSystem::Task task;
};