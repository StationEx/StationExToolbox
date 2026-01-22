#include <print>

#include "args/args.hpp"

#include "WorldXmlDocument.h"
#include "WorldXmlReader.h"

using namespace StationExToolbox;

static args::Group GlobalArguments("arguments");
static args::ValueFlag<std::string> FileFlag(GlobalArguments, "file", "The path to the world.xml file.", { "f", "file" });
static args::HelpFlag HelpFlag(GlobalArguments, "help", "Display this help menu.", { "h", "help" });

static void ThingsListCommand()
{
	WorldXmlReader reader(WorldXmlDocument::FromFile(args::get(FileFlag)));

	std::vector<ThingSaveData> things = reader.GetThings();

	for (const ThingSaveData thing : things)
	{
		std::println("[{}:{}]", thing.GetType(), thing.GetReferenceId());
	}
}

static void ThingsCommand(args::Subparser& parser)
{
	args::Positional<std::string> actionArgument(parser, "action", "list", args::Options::Required);
	parser.Parse();

	std::string action = args::get(actionArgument);
	if (action == "list")
	{
		ThingsListCommand();
	}
}

static void PlayersListCommand()
{

}

static void PlayersCommand(args::Subparser& parser)
{
	args::Positional<std::string> actionArgument(parser, "action", "list", args::Options::Required);
	parser.Parse();

	std::string action = args::get(actionArgument);
	if (action == "list")
	{
		PlayersListCommand();
	}
}

int main(int argc, const char* const argv[])
{
	args::ArgumentParser parser("StationEx Toolbox - A utility for manipulating your Stationeers saves.");

	args::Command thingsCommand(parser, "things", "Commands related to things", &ThingsCommand);
	args::Command playersCommand(parser, "players", "Commands related to players", &PlayersCommand);

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
	catch (const std::exception& e)
	{
		std::println("Fatal Error: {}", e.what());
		return 2;
	}

	return 0;
}