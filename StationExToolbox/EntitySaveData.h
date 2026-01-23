#pragma once

#include "XmlHelper.h"
#include "EntityState.h"
#include "DynamicThingSaveData.h"

namespace StationExToolbox
{
	class EntitySaveData : public DynamicThingSaveData
	{
		public:
		inline EntitySaveData(const XmlNode* const root)
			: DynamicThingSaveData(root)
		{

		}

		bool TryGetState(EntityState& state) const noexcept;

		EntityState GetState() const;
	};
}