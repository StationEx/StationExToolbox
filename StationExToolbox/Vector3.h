#pragma once

#include <string_view>

using namespace std::string_view_literals;

namespace StationExToolbox
{
	struct Vector3
	{
		inline static constexpr std::string_view XElement = "x"sv;
		inline static constexpr std::string_view YElement = "y"sv;
		inline static constexpr std::string_view ZElement = "z"sv;

		float X;
		float Y;
		float Z;
	};
}