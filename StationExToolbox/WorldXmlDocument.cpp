#include "WorldXmlDocument.h"

#include "WorldData.h"
#include "Things.h"

using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

using namespace StationExToolbox;

static bool ReadUInt64FromNode(const XmlNode * const node, std::uint64_t& value) noexcept
{
	const char * const nodeValueEnd = node->value() + node->value_size();
	auto [ptr, _] = std::from_chars(node->value(), nodeValueEnd, value);

	return ptr == nodeValueEnd;
}

static XmlNode* GetThingContainerNode(const XmlDocument& document) noexcept
{
	XmlNode* worldDataNode = document.first_node(WorldData::Element.data(), WorldData::Element.size());
	if (worldDataNode == nullptr)
	{
		return nullptr;
	}

	return worldDataNode->first_node(Things::Element.data(), Things::Element.size());
}

std::expected<Human, Error> WorldXmlDocument::GetHumanByReferenceId(const std::uint64_t referenceId) const noexcept
{
	const XmlNode* const things = GetThingContainerNode(this->document);
	if (things == nullptr)
	{
		return std::unexpected(Error::SaveFormatInvalid);
	}

	const XmlNode* node = things->first_node(Human::Element.data(), Human::Element.size());
	while (node != nullptr)
	{
		const XmlAttribute* const attribute = node->first_attribute("xsi:type");
		if (attribute != nullptr && std::string_view(attribute->value(), attribute->value_size()) == Human::ElementType)
		{
			const XmlNode* const referenceIdElement = node->first_node(Human::ReferenceIdElement.data(), Human::ReferenceIdElement.size());
			if (referenceIdElement == nullptr)
			{
				return std::unexpected(Error::EntityFormatInvalid);
			}

			std::uint64_t currentReferenceId;
			if (!ReadUInt64FromNode(referenceIdElement, currentReferenceId))
			{
				return std::unexpected(Error::EntityFormatInvalid);
			}

			const XmlNode* const steamIdElement = node->first_node(Human::SteamIdElement.data(), Human::SteamIdElement.size());
			if (steamIdElement == nullptr)
			{
				return std::unexpected(Error::EntityFormatInvalid);
			}

			std::uint64_t steamId;
			if (!ReadUInt64FromNode(steamIdElement, steamId))
			{
				return std::unexpected(Error::EntityFormatInvalid);
			}

			if (currentReferenceId == referenceId)
			{
				const XmlNode* const nameElement = node->first_node(Human::NameElement.data(), Human::NameElement.size());
				if (nameElement == nullptr)
				{
					return std::unexpected(Error::EntityFormatInvalid);
				}

				return Human(referenceId, steamId, std::string_view(nameElement->value(), nameElement->value_size()));
			}
		}

		node = node->next_sibling(Human::Element.data(), Human::Element.size());
	}

	return std::unexpected(Error::EntityNotFound);
}