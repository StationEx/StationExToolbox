#pragma once

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
		inline static constexpr std::string_view SteamIdElement = "OwnerSteamId"sv;
		inline static constexpr std::string_view NameElement = "CustomName"sv;

		std::uint64_t ReferenceId;
		std::uint64_t SteamId;
		std::string_view Name;
	};
}