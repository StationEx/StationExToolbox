#pragma once

#include "XmlHelper.h"
#include "EntitySaveData.h"

namespace StationExToolbox
{
	class HumanSaveData : public EntitySaveData
	{
		public:
		inline HumanSaveData(const XmlNode* const root)
			: EntitySaveData(root)
		{
		}
	};
}