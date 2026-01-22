#include "WorldXmlDocument.h"

#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view WorldDataElement = "WorldData"sv;
static constexpr std::string_view AllThingsElement = "AllThings"sv;

StationExToolbox::WorldXmlDocument StationExToolbox::WorldXmlDocument::FromFile(std::filesystem::path path)
{
	const std::size_t fileSize = std::filesystem::file_size(path);

	std::basic_ifstream<char> stream(path, std::ios::binary);
	if (!stream.is_open())
	{
		throw std::runtime_error("The specified file could not be opened.");
	}

	stream.unsetf(std::ios::skipws);

	const std::size_t bufferSize = fileSize + 1;
	std::unique_ptr<char[]> content = std::make_unique_for_overwrite<char[]>(bufferSize);

	stream.read(content.get(), fileSize);
	content[bufferSize - 1] = '\0';

	std::unique_ptr<XmlDocument> document = std::make_unique<XmlDocument>();
	document->parse<rapidxml::parse_non_destructive>(content.get());

	return StationExToolbox::WorldXmlDocument(std::move(content), std::move(document));
}

XmlNode* StationExToolbox::WorldXmlDocument::TryGetAllThingsElement() const noexcept
{
	const XmlNode* const worldDataNode = this->document->first_node(WorldDataElement.data(), WorldDataElement.size());
	if (worldDataNode == nullptr)
	{
		return nullptr;
	}

	return worldDataNode->first_node(AllThingsElement.data(), AllThingsElement.size());
}