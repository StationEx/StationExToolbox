#include "WorldXmlDocument.h"

#include "WorldData.h"
#include "Things.h"
#include "Vector3.h"
#include "Quaternion.h"

#include <cstdint>

using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

using namespace StationExToolbox;

static bool ReadUInt64FromNode(const XmlNode* const node, std::uint64_t& value) noexcept
{
	const char* const nodeValueEnd = node->value() + node->value_size();
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

static bool ReadQuaternionFromNode(const XmlNode* const node, Quaternion& value) noexcept
{
	const XmlNode* const xNode = node->first_node(Quaternion::XElement.data(), Quaternion::XElement.size());
	if (xNode == nullptr || !ReadSingleFromNode(xNode, value.X))
	{
		return false;
	}

	const XmlNode* const yNode = node->first_node(Quaternion::YElement.data(), Quaternion::YElement.size());
	if (yNode == nullptr || !ReadSingleFromNode(yNode, value.Y))
	{
		return false;
	}

	const XmlNode* const zNode = node->first_node(Quaternion::ZElement.data(), Quaternion::ZElement.size());
	if (zNode == nullptr || !ReadSingleFromNode(zNode, value.Z))
	{
		return false;
	}

	const XmlNode* const wNode = node->first_node(Quaternion::WElement.data(), Quaternion::WElement.size());
	if (wNode == nullptr || !ReadSingleFromNode(wNode, value.W))
	{
		return false;
	}

	return true;
}

static bool ReadHumanFromNode(const XmlNode* const node, Human& human) noexcept
{
	const XmlNode* const referenceIdNode = node->first_node(Human::ReferenceIdElement.data(), Human::ReferenceIdElement.size());
	if (referenceIdNode == nullptr || !ReadUInt64FromNode(referenceIdNode, human.ReferenceId))
	{
		return false;
	}

	const XmlNode* const steamIdNode = node->first_node(Human::SteamIdElement.data(), Human::SteamIdElement.size());
	if (steamIdNode == nullptr || !ReadUInt64FromNode(steamIdNode, human.SteamId))
	{
		return false;
	}

	const XmlNode* const nameNode = node->first_node(Human::NameElement.data(), Human::NameElement.size());
	if (nameNode == nullptr)
	{
		return false;
	}

	human.Name = std::string_view(nameNode->value(), nameNode->value_size());

	const XmlNode* const positionNode = node->first_node(Human::PositionElement.data(), Human::PositionElement.size());
	if (positionNode == nullptr || !ReadVector3FromNode(positionNode, human.Position))
	{
		return false;
	}

	const XmlNode* const rotationNode = node->first_node(Human::RotationElement.data(), Human::RotationElement.size());
	if (rotationNode == nullptr || !ReadQuaternionFromNode(rotationNode, human.Rotation))
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