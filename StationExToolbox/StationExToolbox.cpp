#include <chrono>
#include <print>

#include "WorldXmlDocument.h"

using namespace StationExToolbox;

int main(int argc, const char* const argv[])
{
	if (argc != 2)
	{
		std::println("Usage: ./StationExToolbox [path]");
		return 0;
	}

	std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();

	WorldXmlDocument* world;
	
	try
	{
		world = new WorldXmlDocument(argv[1]);
	}
	catch (...)
	{
		world = nullptr;
	}

	if (world == nullptr)
	{
		std::println("Failed to open the specified file \"{}\".", argv[1]);
		return 1;
	}

	std::expected<Human, Error> result = world->GetHumanById(7724035);
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