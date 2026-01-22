#include "WorldXmlReader.h"
#include "ThingSaveData.h"

#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view ThingElement = "ThingSaveData"sv;

std::vector<StationExToolbox::ThingSaveData> StationExToolbox::WorldXmlReader::GetThings() const
{
	std::vector<ThingSaveData> things;
	if (TryGetThings(things))
	{
		return things;
	}

	throw std::runtime_error("Failed to read ThingSaveData because the containing element is missing or improperly formatted.");
}

bool StationExToolbox::WorldXmlReader::TryGetThings(std::vector<ThingSaveData>& things) const noexcept
{
	const XmlNode* const allThingsNode = this->document.TryGetAllThingsElement();
	if (allThingsNode == nullptr)
	{
		return false;
	}

	const XmlNode* currentThingNode = allThingsNode->first_node(ThingElement.data(), ThingElement.size());
	while (currentThingNode != nullptr)
	{
		things.emplace_back(currentThingNode);
		currentThingNode = currentThingNode->next_sibling(ThingElement.data(), ThingElement.size());
	}

	return true;
}