#include <emscripten/bind.h>
#include <print>
#include <fstream>
#include <filesystem>
#include <format>

#include "args/args.hpp"

#include "WorldXmlDocument.h"
#include "WorldXmlReader.h"

using namespace StationExToolbox;
using namespace emscripten;

std::string parseWorldXml(const std::string& xmlContent)
{
    // Create a temporary file to hold the XML content
    std::filesystem::path tempFilePath = std::filesystem::temp_directory_path() / "temp_world.xml";
    {
        std::ofstream tempFile(tempFilePath);
        tempFile << xmlContent;
    }

    WorldXmlReader reader(WorldXmlDocument::FromFile(tempFilePath));

    std::vector<ThingSaveData> things = reader.GetThings();

    std::string result;
    for (const ThingSaveData& thing : things)
    {
        result += std::format("[{}:{}] \"{}\" is at {}\n",
            thing.GetType(), thing.GetReferenceId(), thing.GetCustomName(), thing.GetWorldPosition());
    }

    // Clean up the temporary file
    std::filesystem::remove(tempFilePath);

    return result;
}

EMSCRIPTEN_BINDINGS(stationex) {
    function("parseWorldXml", &parseWorldXml);
}

int main()
{
	return 0;
}
