#pragma once

#include "XmlHelper.h"
#include "Vector3.h"
#include "ThingSaveData.h"

#include <cstdint>

namespace StationExToolbox
{
	class DynamicThingSaveData : public ThingSaveData
	{
		public:
		inline DynamicThingSaveData(const XmlNode* const root)
			: ThingSaveData(root)
		{
		}

		[[nodiscard]]
		bool TryGetParentReferenceId(std::uint64_t& parentReferenceId) const noexcept;

		std::uint64_t GetParentReferenceId() const;

		[[nodiscard]]
		bool TryGetParentSlotId(std::uint32_t& parentSlotId) const noexcept;

		std::uint32_t GetParentSlotId() const;

		[[nodiscard]]
		bool TryGetDragOffset(Vector3& dragOffset) const noexcept;

		Vector3 GetDragOffset() const;

		[[nodiscard]]
		bool TryGetVelocity(Vector3& velocity) const noexcept;

		Vector3 GetVelocity() const;

		[[nodiscard]]
		bool TryGetAngularVelocity(Vector3& angularVelocity) const noexcept;

		Vector3 GetAngularVelocity() const;

		[[nodiscard]]
		bool TryGetCurrentHealth(float& currentHealth) const noexcept;

		float GetCurrentHealth() const;
	};
}