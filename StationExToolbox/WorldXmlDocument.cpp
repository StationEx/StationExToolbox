#include "WorldXmlDocument.h"

#include "WorldData.h"
#include "Things.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <cstdint>

using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

using namespace StationExToolbox;

static bool ReadUInt64FromNode(const XmlNode * const node, std::uint64_t& value) noexcept
{
	const char * const nodeValueEnd = node->value() + node->value_size();
	auto [ptr, _] = std::from_chars(node->value(), nodeValueEnd, value);

	return ptr == nodeValueEnd;
}

static bool ReadSingleFromNode(const XmlNode* const node, float& value) noexcept
{
	const char* const nodeValueEnd = node->value() + node->value_size();
	auto [ptr, _] = std::from_chars(node->value(), nodeValueEnd, value);

	return ptr == nodeValueEnd;
}

static bool ReadVector3FromNode(const XmlNode* const node, Vector3& value) noexcept
{
	const XmlNode* const xNode = node->first_node(Vector3::XElement.data(), Vector3::XElement.size());
	if (xNode == nullptr || !ReadSingleFromNode(xNode, value.X))
	{
		return false;
	}

	const XmlNode* const yNode = node->first_node(Vector3::YElement.data(), Vector3::YElement.size());
	if (yNode == nullptr || !ReadSingleFromNode(yNode, value.Y))
	{
		return false;
	}

	const XmlNode* const zNode = node->first_node(Vector3::ZElement.data(), Vector3::ZElement.size());
	if (zNode == nullptr || !ReadSingleFromNode(zNode, value.Z))
	{
		return false;
	}

	return true;
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

Error WorldXmlDocument::GetHumanByReferenceId(const std::uint64_t referenceId, Human& entity) const noexcept
{
	const XmlNode* const things = GetThingContainerNode(this->document);
	if (things == nullptr)
	{
		return Error::SaveFormatInvalid;
	}

	const XmlNode* thingNode = things->first_node(Human::Element.data(), Human::Element.size());
	while (thingNode != nullptr)
	{
		const XmlAttribute* const thingTypeAttribute = thingNode->first_attribute("xsi:type");
		if (thingTypeAttribute != nullptr && std::string_view(thingTypeAttribute->value(), thingTypeAttribute->value_size()) == Human::ElementType)
		{
			const XmlNode* const referenceIdElement = thingNode->first_node(Human::ReferenceIdElement.data(), Human::ReferenceIdElement.size());
			if (referenceIdElement == nullptr || !ReadUInt64FromNode(referenceIdElement, entity.ReferenceId))
			{
				return Error::EntityFormatInvalid;
			}

			const XmlNode* const steamIdElement = thingNode->first_node(Human::SteamIdElement.data(), Human::SteamIdElement.size());
			if (steamIdElement == nullptr || !ReadUInt64FromNode(steamIdElement, entity.SteamId))
			{
				return Error::EntityFormatInvalid;
			}

			if (entity.ReferenceId == referenceId)
			{
				const XmlNode* const nameElement = thingNode->first_node(Human::NameElement.data(), Human::NameElement.size());
				if (nameElement == nullptr)
				{
					return Error::EntityFormatInvalid;
				}

				entity.Name = std::string_view(nameElement->value(), nameElement->value_size());
				return Error::None;
			}
		}

		thingNode = thingNode->next_sibling(Human::Element.data(), Human::Element.size());
	}

	return Error::EntityNotFound;
}