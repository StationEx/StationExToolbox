#pragma once

#include <string_view>

using namespace std::string_view_literals;

namespace StationExToolbox
{
	class WorldData
	{
		public:
		inline static constexpr std::string_view Element = "WorldData"sv;
	};
}