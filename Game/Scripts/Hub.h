#pragma once
#include "components\Behaviour.h"
#include <vector>
#include <map>

struct Slot;

class Hub : public Behaviour
{
public:
	static Hub *Create(GameObject* gameObject);
	void AddStructureToNetwork(enum StructureType type, class Structure* structure, int x, int y);
	class Structure* GetStructure(int x, int y);
	class Structure* FindNearest(enum StructureType type, int x, int y);

	void Copy(GameObject *copyObject);
private:
	std::vector<Slot> networkList;
	std::vector<Slot> warehouseList;
	std::map<int, std::map<int, class Structure*>> networkSlots;
};