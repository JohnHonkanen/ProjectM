/*
Warehouse class used to store and send/recieve resources
Dev: Jack Smith (B000308927)
*/

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Structure.h"
#include <array>

using namespace std;
using namespace glm;

namespace Engine {
	class Warehouse : public Structure {
	private:
		std::array<string,9> storage; //std::array used for storing objects - used because accesing size is easy with it.
		bool storageFull = false;
		int itemsStored =0;
	
	public:
		void Update(int change);
		string DisplayContents();
		void SetStorageSize(int change) { storage[9 + change]; }
		int GetItemsStored() { return itemsStored; }
		
		void SendItem();
		void ReceiveItem();
		bool CheckItem(string itemType);
		void PlaceItem();

		// Serilazation method to store the required variables to an xml document.
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(storage), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(radiationOutput), CEREAL_NVP(pos), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive));
		}
	};
}
