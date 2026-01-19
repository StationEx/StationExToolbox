#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <print>

#include "WorldXmlDocument.h"

using namespace StationExToolbox;

static std::unique_ptr<char[]> ReadFile(std::basic_ifstream<char>& stream, const std::size_t streamSize)
{
	stream.unsetf(std::ios::skipws);

	const std::size_t bufferSize = streamSize + 1;
	std::unique_ptr<char[]> buffer = std::make_unique_for_overwrite<char[]>(bufferSize);

	stream.read(buffer.get(), streamSize);
	buffer[bufferSize - 1] = '\0';

	return buffer;
}

int main(int argc, const char* const argv[])
{
	if (argc != 2)
	{
		std::println("Usage: ./StationExToolbox [path]");
		return 0;
	}

	std::filesystem::path pathArgument(argv[1]);

	std::basic_ifstream<char> stream(pathArgument, std::ios::binary);
	if (!stream.is_open())
	{
		std::println("Failed to open file.");
		return 1;
	}

	std::unique_ptr<char[]> buffer = ReadFile(stream, std::filesystem::file_size(pathArgument));
	stream.close();

	std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();

	WorldXmlDocument* worldXml = new WorldXmlDocument(std::move(buffer));
	if (!worldXml->Parse())
	{
		std::println("Failed to open and parse the specified file \"{}\".", argv[1]);
		return 1;
	}

	std::expected<Human, Error> result = worldXml->GetHumanByReferenceId(7724035);
	std::chrono::time_point endTime = std::chrono::high_resolution_clock::now();

	std::println("Parse time was {}ms", std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());

	if (result.has_value())
	{
		Human human = result.value();
		std::println("Found player \"{}\" with reference id {}.", human.GetName(), human.GetReferenceId());
	}
	else
	{
		std::println("Couldn't find player.");
	}

	return 0;
}