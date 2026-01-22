#pragma once

#include <format>
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

template<> struct std::formatter<StationExToolbox::Vector3> : std::formatter<std::string>
{
	template<class FormatContext>
	auto format(const StationExToolbox::Vector3& value, FormatContext& context) const
	{
		return std::formatter<std::string>::format(std::format("({}, {}, {})", value.X, value.Y, value.Z), context);
	}
};