#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <print>

#include "args/args.hpp"

#include "WorldXmlDocument.h"

using namespace StationExToolbox;

static args::Group GlobalArguments("arguments");
static args::ValueFlag<std::string> FileFlag(GlobalArguments, "file", "The path to the world.xml file.", { "f", "file" });
static args::HelpFlag HelpFlag(GlobalArguments, "help", "Display this help menu.", { "h", "help" });

static std::unique_ptr<char[]> ReadFile(std::basic_ifstream<char>& stream, const std::size_t streamSize) noexcept
{
	stream.unsetf(std::ios::skipws);

	const std::size_t bufferSize = streamSize + 1;
	std::unique_ptr<char[]> buffer = std::make_unique_for_overwrite<char[]>(bufferSize);

	stream.read(buffer.get(), streamSize);
	buffer[bufferSize - 1] = '\0';

	return buffer;
}

static std::unique_ptr<WorldXmlDocument> GetWorldXmlDocument(std::filesystem::path path) noexcept
{
	std::basic_ifstream<char> stream(path, std::ios::binary);
	if (!stream.is_open())
	{
		return nullptr;
	}

	return std::make_unique<WorldXmlDocument>(ReadFile(stream, std::filesystem::file_size(path)));
}

static void ListPlayersCommand() noexcept
{
	std::unique_ptr<WorldXmlDocument> world = GetWorldXmlDocument(args::get(FileFlag));
	if (world == nullptr)
	{
		std::println("Error: The save file could not be opened.");
		return;
	}

	if (!world->Parse())
	{
		std::println("Error: The save file is malformed.");
		return;
	}

	std::vector<Human> humans;
	if (world->GetHumans(humans) != Error::None)
	{
		std::println("Error: The save file is in an unexpected format.");
		return;
	}

	for (const Human& human : humans)
	{
		std::println("[{}] \"{}\" ({}) is {} at ({}, {}, {})",
			human.ReferenceId, human.Name, human.SteamId, human.State, human.Position.X, human.Position.Y, human.Position.Z);
	}
}

static void HandlePlayersCommand(args::Subparser& parser) noexcept
{
	args::Positional<std::string> actionArgument(parser, "action", "list", args::Options::Required);
	parser.Parse();

	std::string action = args::get(actionArgument);

	if (action == "list")
	{
		ListPlayersCommand();
	}
}

int main(int argc, const char* const argv[])
{
	args::ArgumentParser parser("StationEx Toolbox - A utility for manipulating your Stationeers saves.");
	args::Command playersCommand(parser, "players", "Commands related to players", &HandlePlayersCommand);

	args::GlobalOptions globalOptions(parser, GlobalArguments);

	try
	{
		parser.ParseCLI(argc, argv);
	}
	catch (const args::Help&)
	{
		std::println("{}", parser.Help());
		return 0;
	}
	catch (const args::Error& e)
	{
		std::println("Error: {}", e.what());
		std::println("{}", parser.Help());
		return 1;
	}

	return 0;
}