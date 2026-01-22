#pragma once

#include "ThingSaveData.h"

#include <stdexcept>
#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view ElementType = "xsi:type"sv;
static constexpr std::string_view ReferenceIdElement = "ReferenceId"sv;
static constexpr std::string_view PrefabNameElement = "PrefabName"sv;
static constexpr std::string_view CustomNameElement = "CustomName"sv;
static constexpr std::string_view WorldPositionElement = "WorldPosition"sv;
static constexpr std::string_view WorldRotationElement = "WorldRotation"sv;

std::string_view StationExToolbox::ThingSaveData::GetType() const
{
	std::string_view type;
	if (TryGetType(type))
	{
		return type;
	}

	throw std::runtime_error("Failed to read ThingSaveData.Type because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetType(std::string_view& type) const noexcept
{
	const XmlAttribute* const typeAttribute = this->root->first_attribute(ElementType.data(), ElementType.size());
	if (typeAttribute == nullptr)
	{
		return false;
	}

	type = std::string_view(typeAttribute->value(), typeAttribute->value_size());
	return true;
}

std::uint64_t StationExToolbox::ThingSaveData::GetReferenceId() const
{
	uint64_t referenceId;
	if (TryGetReferenceId(referenceId))
	{
		return referenceId;
	}

	throw std::runtime_error("Failed to read ThingSaveData.ReferenceId because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetReferenceId(std::uint64_t& referenceId) const noexcept
{
	const XmlNode* const referenceIdNode = this->root->first_node(ReferenceIdElement.data(), ReferenceIdElement.size());
	if (referenceIdNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetUInt64(referenceIdNode, referenceId);
}

std::string_view StationExToolbox::ThingSaveData::GetPrefabName() const
{
	std::string_view prefabName;
	if (TryGetPrefabName(prefabName))
	{
		return prefabName;
	}

	throw std::runtime_error("Failed to read ThingSaveData.PrefabName because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetPrefabName(std::string_view& prefabName) const noexcept
{
	const XmlNode* const prefabNameNode = this->root->first_node(PrefabNameElement.data(), PrefabNameElement.size());
	if (prefabNameNode == nullptr)
	{
		return false;
	}

	prefabName = std::string_view(prefabNameNode->value(), prefabNameNode->value_size());
	return true;
}

std::string_view StationExToolbox::ThingSaveData::GetCustomName() const
{
	std::string_view customName;
	if (TryGetCustomName(customName))
	{
		return customName;
	}

	throw std::runtime_error("Failed to read ThingSaveData.CustomName because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetCustomName(std::string_view& customName) const noexcept
{
	const XmlNode* const customNameNode = this->root->first_node(CustomNameElement.data(), CustomNameElement.size());
	if (customNameNode == nullptr)
	{
		return false;
	}

	customName = std::string_view(customNameNode->value(), customNameNode->value_size());
	return true;
}

StationExToolbox::Vector3 StationExToolbox::ThingSaveData::GetWorldPosition() const
{
	Vector3 worldPosition;
	if (TryGetWorldPosition(worldPosition))
	{
		return worldPosition;
	}

	throw std::runtime_error("Failed to read ThingSaveData.WorldPosition because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetWorldPosition(Vector3& worldPosition) const noexcept
{
	const XmlNode* const worldPositionNode = this->root->first_node(WorldPositionElement.data(), WorldPositionElement.size());
	if (worldPositionNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetVector3(worldPositionNode, worldPosition);
}

StationExToolbox::Quaternion StationExToolbox::ThingSaveData::GetWorldRotation() const
{
	Quaternion worldRotation;
	if (TryGetWorldRotation(worldRotation))
	{
		return worldRotation;
	}

	throw std::runtime_error("Failed to read ThingSaveData.WorldRotation because the element is missing or improperly formatted.");
}

bool StationExToolbox::ThingSaveData::TryGetWorldRotation(Quaternion& worldRotation) const noexcept
{
	const XmlNode* const worldRotationNode = this->root->first_node(WorldRotationElement.data(), WorldRotationElement.size());
	if (worldRotationNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetQuaternion(worldRotationNode, worldRotation);
}
