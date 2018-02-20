#include "Hub.h"
#include "Structure.h"

struct Slot
{
	StructureType type;
	int x, y;
	class Structure *structure;
};

Hub * Hub::Create(GameObject * gameObject)
{
	Hub *h = new Hub();
	gameObject->AddComponent(h);

	return h;

}

void Hub::AddStructureToNetwork(StructureType type, Structure * structure, int x, int y)
{
	switch (type)
	{
	case PRODUCTION:
		networkList.push_back({type, x, y, structure});
		break;
	case WAREHOUSE:
		networkList.push_back({ type, x, y, structure });
		warehouseList.push_back({ type, x, y, structure });
		break;
	case FACTORY:
		networkList.push_back({ type, x, y, structure });
		break;
	default:
		break;
	}

	networkSlots[x][y] = structure;
}

Structure * Hub::GetStructure(int x, int y)
{
	if (networkSlots.find(x) != networkSlots.end())
	{
		//Found
		std::map<int, Structure*> netSlotsY = networkSlots[x];
		if (netSlotsY.find(y) != netSlotsY.end())
		{
			return netSlotsY[y];
		}
	}

	return nullptr;
}

Structure * Hub::FindNearest(StructureType type, int x, int y)
{
	int distance = 1000000000;
	Structure * s = nullptr;

	for (int i = 0; i < networkList.size(); i++)
	{
		//Not the type we are looking for
		if (networkList[i].type != type)
		{
			continue;
		}

		int dx, dy;
		dx = (networkList[i].x - x);
		dy = abs(networkList[i].y - y);
		int dist = (dx*dx) + (dy*dy);
		if (dist < distance)
		{
			distance = dist;
			s = networkList[i].structure;
		}
		
	}

	return s;
}

void Hub::Copy(GameObject * copyObject)
{
	//TO Be Filled in
}
