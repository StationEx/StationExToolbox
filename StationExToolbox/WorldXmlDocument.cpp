#include "WorldXmlDocument.h"

#include "WorldData.h"
#include "Things.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "XmlHelper.h"

#include <cstdint>

using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

using namespace StationExToolbox;

static bool ReadHumanFromNode(const XmlNode* const node, Human& human) noexcept
{
	const XmlNode* const referenceIdNode = node->first_node(Human::ReferenceIdElement.data(), Human::ReferenceIdElement.size());
	if (referenceIdNode == nullptr || !XmlHelper::TryGetUInt64(referenceIdNode, human.ReferenceId))
	{
		return false;
	}

	const XmlNode* const parentReferenceIdNode = node->first_node(Human::ParentReferenceIdElement.data(), Human::ParentReferenceIdElement.size());
	if (parentReferenceIdNode == nullptr)
	{
		human.ParentReferenceId = std::nullopt;
	}
	else
	{
		std::uint64_t parentReferenceId;
		if (!XmlHelper::TryGetUInt64(parentReferenceIdNode, parentReferenceId))
		{
			return false;
		}

		human.ParentReferenceId = parentReferenceId;
	}

	const XmlNode* const steamIdNode = node->first_node(Human::SteamIdElement.data(), Human::SteamIdElement.size());
	if (steamIdNode == nullptr || !XmlHelper::TryGetUInt64(steamIdNode, human.SteamId))
	{
		return false;
	}

	const XmlNode* const nameNode = node->first_node(Human::NameElement.data(), Human::NameElement.size());
	if (nameNode == nullptr)
	{
		return false;
	}

	human.Name = std::string_view(nameNode->value(), nameNode->value_size());

	const XmlNode* const stateNode = node->first_node(Human::StateElement.data(), Human::StateElement.size());
	if (stateNode == nullptr)
	{
		return false;
	}

	human.State = std::string_view(stateNode->value(), stateNode->value_size());

	const XmlNode* const positionNode = node->first_node(Human::PositionElement.data(), Human::PositionElement.size());
	if (positionNode == nullptr || !XmlHelper::TryGetVector3(positionNode, human.Position))
	{
		return false;
	}

	const XmlNode* const rotationNode = node->first_node(Human::RotationElement.data(), Human::RotationElement.size());
	if (rotationNode == nullptr || !XmlHelper::TryGetQuaternion(rotationNode, human.Rotation))
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

Error WorldXmlDocument::GetHumans(std::vector<Human>& humans) const noexcept
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
			Human human;
			if (!ReadHumanFromNode(thingNode, human))
			{
				return Error::EntityFormatInvalid;
			}

			humans.push_back(std::move(human));
		}

		thingNode = thingNode->next_sibling(Human::Element.data(), Human::Element.size());
	}

	return Error::None;
}

Error WorldXmlDocument::GetHumanByReferenceId(const std::uint64_t referenceId, Human& human) const noexcept
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
			if (!ReadHumanFromNode(thingNode, human))
			{
				return Error::EntityFormatInvalid;
			}

			if (human.ReferenceId == referenceId)
			{
				return Error::None;
			}
		}

		thingNode = thingNode->next_sibling(Human::Element.data(), Human::Element.size());
	}

	return Error::EntityNotFound;
}