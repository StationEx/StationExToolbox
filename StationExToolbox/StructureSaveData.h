#pragma once

#include "XmlHelper.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "ThingSaveData.h"

#include <cstdint>

namespace StationExToolbox
{
	class StructureSaveData : ThingSaveData
	{
		public:
		inline StructureSaveData(const XmlNode* const root) noexcept
			: ThingSaveData(root)
		{
		}

		[[nodiscard]]
		bool TryGetCurrentBuildState(std::uint32_t& currentBuildState) const noexcept;

		std::uint32_t GetCurrentBuildState() const;

		[[nodiscard]]
		bool TryGetRegisteredWorldPosition(Vector3& registeredWorldPosition) const noexcept;

		Vector3 GetRegisteredWorldPosition() const;

		[[nodiscard]]
		bool TryGetRegisteredWorldRotation(Quaternion& registeredWorldRotation) const noexcept;

		Quaternion GetRegisteredWorldRotation() const;
	};
}