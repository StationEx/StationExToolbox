#pragma once

namespace StationExToolbox
{
	struct Quaternion
	{
		inline static constexpr std::string_view XElement = "x"sv;
		inline static constexpr std::string_view YElement = "y"sv;
		inline static constexpr std::string_view ZElement = "z"sv;
		inline static constexpr std::string_view WElement = "w"sv;

		float X;
		float Y;
		float Z;
		float W;
	};
}