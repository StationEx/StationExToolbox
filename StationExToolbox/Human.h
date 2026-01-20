#pragma once

#include "Vector3.h"
#include "Quaternion.h"

#include <optional>
#include <memory>
#include <string_view>

using namespace std::string_view_literals;

namespace StationExToolbox
{
	struct Human
	{
		inline static constexpr std::string_view Element = "ThingSaveData"sv;
		inline static constexpr std::string_view ElementType = "HumanSaveData"sv;
		inline static constexpr std::string_view ReferenceIdElement = "ReferenceId"sv;
		inline static constexpr std::string_view ParentReferenceIdElement = "ParentReferenceId"sv;
		inline static constexpr std::string_view SteamIdElement = "OwnerSteamId"sv;
		inline static constexpr std::string_view NameElement = "CustomName"sv;
		inline static constexpr std::string_view StateElement = "State"sv;
		inline static constexpr std::string_view PositionElement = "WorldPosition"sv;
		inline static constexpr std::string_view RotationElement = "WorldRotation"sv;

		std::uint64_t ReferenceId;
		std::optional<std::uint64_t> ParentReferenceId;
		std::uint64_t SteamId;
		std::string_view Name;
		std::string_view State;
		Vector3 Position;
		Quaternion Rotation;
	};
}