#pragma once

#include "XmlHelper.h"

namespace StationExToolbox
{
	class ThingSaveData
	{
		private:
		const XmlNode* const root;

		public:
		inline ThingSaveData(const XmlNode* const root) noexcept
			: root(root)
		{

		}

		std::string_view GetType() const;

		[[nodiscard]]
		bool TryGetType(std::string_view& type) const noexcept;

		std::uint64_t GetReferenceId() const;

		[[nodiscard]]
		bool TryGetReferenceId(std::uint64_t& referenceId) const noexcept;
		
		std::string_view GetPrefabName() const;

		[[nodiscard]]
		bool TryGetPrefabName(std::string_view& prefabName) const noexcept;

		std::string_view GetCustomName() const;

		[[nodiscard]]
		bool TryGetCustomName(std::string_view& customName) const noexcept;

		Vector3 GetWorldPosition() const;

		[[nodiscard]]
		bool TryGetWorldPosition(Vector3& worldPosition) const noexcept;

		Quaternion GetWorldRotation() const;

		[[nodiscard]]
		bool TryGetWorldRotation(Quaternion& worldRotation) const noexcept;
	};
}