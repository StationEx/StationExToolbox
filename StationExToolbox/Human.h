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
		const std::string_view name;

		public:
		inline static constexpr std::string_view Element = "ThingSaveData"sv;
		inline static constexpr std::string_view ElementType = "HumanSaveData"sv;
		inline static constexpr std::string_view ReferenceIdElement = "ReferenceId"sv;
		inline static constexpr std::string_view NameElement = "Name"sv;

		inline Human(std::uint64_t referenceId, std::string_view name)
			: referenceId(referenceId), name(std::move(name))
		{

		}

		inline std::uint64_t GetReferenceId() const
		{
			return this->referenceId;
		}

		inline std::string_view GetName() const
		{
			return this->name;
		}
	};
}