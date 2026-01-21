#pragma once

#include "XmlHelper.h"

namespace StationExToolbox
{
	class ThingSaveData
	{
		private:
		XmlNode* const root;

		public:
		inline ThingSaveData(XmlNode* const root) noexcept
			: root(root)
		{

		}

		[[nodiscard]]
		bool TryGetReferenceId(std::uint64_t& referenceId) const noexcept;
		
		[[nodiscard]]
		bool TryGetPrefabName(std::string_view& prefabName) const noexcept;
	};
}