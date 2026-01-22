#pragma once

#include "WorldXmlDocument.h"
#include "ThingSaveData.h"

#include <memory>
#include <vector>

namespace StationExToolbox
{
	class WorldXmlReader
	{
		private:
		WorldXmlDocument document;

		public:
		inline WorldXmlReader(WorldXmlDocument document)
			: document(std::move(document))
		{

		}

		std::vector<ThingSaveData> GetThings() const;

		[[nodiscard]]
		bool TryGetThings(std::vector<ThingSaveData>& things) const noexcept;
	};
}