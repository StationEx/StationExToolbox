#pragma once

#include <memory>
#include <string_view>

using namespace std::string_view_literals;

namespace StationExToolbox
{
	class Human
	{
		private:
		const std::uint64_t referenceId;
		const std::uint64_t steamId;
		const std::string_view name;

		public:
		inline static constexpr std::string_view Element = "ThingSaveData"sv;
		inline static constexpr std::string_view ElementType = "HumanSaveData"sv;
		inline static constexpr std::string_view ReferenceIdElement = "ReferenceId"sv;
		inline static constexpr std::string_view SteamIdElement = "OwnerSteamId"sv;
		inline static constexpr std::string_view NameElement = "CustomName"sv;

		inline Human(std::uint64_t referenceId, std::uint64_t steamId, std::string_view name)
			: referenceId(referenceId), steamId(steamId), name(std::move(name))
		{

		}

		inline std::uint64_t GetReferenceId() const
		{
			return this->referenceId;
		}

		inline std::uint64_t GetSteamId() const
		{
			return this->steamId;
		}

		inline std::string_view GetName() const
		{
			return this->name;
		}
	};
}