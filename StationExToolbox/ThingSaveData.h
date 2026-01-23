#pragma once

#include "XmlHelper.h"

namespace StationExToolbox
{
	class ThingSaveData
	{
		protected:
		const XmlNode* const root;

		public:
		inline ThingSaveData(const XmlNode* const root) noexcept
			: root(root)
		{

		}

		[[nodiscard]]
		bool TryGetType(std::string_view& type) const noexcept;

		std::string_view GetType() const;

		[[nodiscard]]
		bool TryGetReferenceId(std::uint64_t& referenceId) const noexcept;

		std::uint64_t GetReferenceId() const;

		[[nodiscard]]
		bool TryGetOwnerSteamId(std::uint64_t& ownerSteamId) const noexcept;

		std::uint64_t GetOwnerSteamId() const;

		[[nodiscard]]
		bool TryGetPrefabName(std::string_view& prefabName) const noexcept;

		std::string_view GetPrefabName() const;

		[[nodiscard]]
		bool TryGetCustomName(std::string_view& customName) const noexcept;

		std::string_view GetCustomName() const;

		[[nodiscard]]
		bool TryGetWorldPosition(Vector3& worldPosition) const noexcept;

		Vector3 GetWorldPosition() const;

		[[nodiscard]]
		bool TryGetWorldRotation(Quaternion& worldRotation) const noexcept;

		Quaternion GetWorldRotation() const;
	};
}