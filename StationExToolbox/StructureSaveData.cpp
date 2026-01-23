#include "StructureSaveData.h"

#include <stdexcept>
#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view CurrentBuildStateElement = "CurrentBuildState"sv;
static constexpr std::string_view RegisteredWorldPositionElement = "RegisteredWorldPosition"sv;
static constexpr std::string_view RegisteredWorldRotationElement = "RegisteredWorldRotation"sv;

bool StationExToolbox::StructureSaveData::TryGetCurrentBuildState(std::uint32_t& currentBuildState) const noexcept
{
	const XmlNode* const currentBuildStateNode = this->root->first_node(CurrentBuildStateElement.data(), CurrentBuildStateElement.size());
	if (currentBuildStateNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetUInt32(currentBuildStateNode, currentBuildState);
}

std::uint32_t StationExToolbox::StructureSaveData::GetCurrentBuildState() const
{
	std::uint32_t currentBuildState;
	if (this->TryGetCurrentBuildState(currentBuildState))
	{
		return currentBuildState;
	}

	throw std::runtime_error("Failed to read StructureSaveData CurrentBuildState because the element is missing or improperly formatted.");
}

bool StationExToolbox::StructureSaveData::TryGetRegisteredWorldPosition(Vector3& registeredWorldPosition) const noexcept
{
	const XmlNode* const registeredWorldPositionNode = this->root->first_node(RegisteredWorldPositionElement.data(), RegisteredWorldPositionElement.size());
	if (registeredWorldPositionNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetVector3(registeredWorldPositionNode, registeredWorldPosition);
}

StationExToolbox::Vector3 StationExToolbox::StructureSaveData::GetRegisteredWorldPosition() const
{
	StationExToolbox::Vector3 registeredWorldPosition;
	if (this->TryGetRegisteredWorldPosition(registeredWorldPosition))
	{
		return registeredWorldPosition;
	}

	throw std::runtime_error("Failed to read StructureSaveData RegisteredWorldPosition because the element is missing or improperly formatted.");
}

bool StationExToolbox::StructureSaveData::TryGetRegisteredWorldRotation(Quaternion& registeredWorldRotation) const noexcept
{
	const XmlNode* const registeredWorldRotationNode = this->root->first_node(RegisteredWorldRotationElement.data(), RegisteredWorldRotationElement.size());
	if (registeredWorldRotationNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetQuaternion(registeredWorldRotationNode, registeredWorldRotation);
}

StationExToolbox::Quaternion StationExToolbox::StructureSaveData::GetRegisteredWorldRotation() const
{
	StationExToolbox::Quaternion registeredWorldRotation;
	if (this->TryGetRegisteredWorldRotation(registeredWorldRotation))
	{
		return registeredWorldRotation;
	}

	throw std::runtime_error("Failed to read StructureSaveData RegisteredWorldRotation because the element is missing or improperly formatted.");
}