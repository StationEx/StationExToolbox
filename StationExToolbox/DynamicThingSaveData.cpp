#include "DynamicThingSaveData.h"

#include <stdexcept>
#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view ParentReferenceIdElement = "ParentReferenceId"sv;
static constexpr std::string_view ParentSlotIdElement = "ParentSlotId"sv;
static constexpr std::string_view DragOffsetElement = "DragOffset"sv;
static constexpr std::string_view VelocityElement = "Velocity"sv;
static constexpr std::string_view AngularVelocityElement = "AngularVelocity"sv;
static constexpr std::string_view CurrentHealthElement = "HealthCurrent"sv;

bool StationExToolbox::DynamicThingSaveData::TryGetParentReferenceId(std::uint64_t& parentReferenceId) const noexcept
{
    const XmlNode* const parentReferenceIdNode = this->root->first_node(ParentReferenceIdElement.data(), ParentReferenceIdElement.size());
    if (parentReferenceIdNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetUInt64(parentReferenceIdNode, parentReferenceId);
}

std::uint64_t StationExToolbox::DynamicThingSaveData::GetParentReferenceId() const
{
    std::uint64_t parentReferenceId;
    if (this->TryGetParentReferenceId(parentReferenceId))
    {
        return parentReferenceId;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData ParentReferenceId because the element is missing or improperly formatted.");
}

bool StationExToolbox::DynamicThingSaveData::TryGetParentSlotId(std::uint32_t& parentSlotId) const noexcept
{
    const XmlNode* const parentSlotIdNode = this->root->first_node(ParentSlotIdElement.data(), ParentSlotIdElement.size());
    if (parentSlotIdNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetUInt32(parentSlotIdNode, parentSlotId);
}

std::uint32_t StationExToolbox::DynamicThingSaveData::GetParentSlotId() const
{
    std::uint32_t parentSlotId;
    if (this->TryGetParentSlotId(parentSlotId))
    {
        return parentSlotId;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData ParentSlotId because the element is missing or improperly formatted.");
}

bool StationExToolbox::DynamicThingSaveData::TryGetDragOffset(Vector3& dragOffset) const noexcept
{
    const XmlNode* const dragOffsetNode = this->root->first_node(DragOffsetElement.data(), DragOffsetElement.size());
    if (dragOffsetNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetVector3(dragOffsetNode, dragOffset);
}

StationExToolbox::Vector3 StationExToolbox::DynamicThingSaveData::GetDragOffset() const
{
    Vector3 dragOffset;
    if (this->TryGetDragOffset(dragOffset))
    {
        return dragOffset;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData DragOffset because the element is missing or improperly formatted.");
}

bool StationExToolbox::DynamicThingSaveData::TryGetVelocity(Vector3& velocity) const noexcept
{
    const XmlNode* const velocityNode = this->root->first_node(VelocityElement.data(), VelocityElement.size());
    if (velocityNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetVector3(velocityNode, velocity);
}

StationExToolbox::Vector3 StationExToolbox::DynamicThingSaveData::GetVelocity() const
{
    Vector3 velocity;
    if (this->TryGetVelocity(velocity))
    {
        return velocity;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData Velocity because the element is missing or improperly formatted.");
}

bool StationExToolbox::DynamicThingSaveData::TryGetAngularVelocity(Vector3& angularVelocity) const noexcept
{
    const XmlNode* const angularVelocityNode = this->root->first_node(AngularVelocityElement.data(), AngularVelocityElement.size());
    if (angularVelocityNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetVector3(angularVelocityNode, angularVelocity);
}

StationExToolbox::Vector3 StationExToolbox::DynamicThingSaveData::GetAngularVelocity() const
{
    Vector3 angularVelocity;
    if (this->TryGetAngularVelocity(angularVelocity))
    {
        return angularVelocity;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData AngularVelocity because the element is missing or improperly formatted.");
}

bool StationExToolbox::DynamicThingSaveData::TryGetCurrentHealth(float& currentHealth) const noexcept
{
    const XmlNode* const currentHealthNode = this->root->first_node(CurrentHealthElement.data(), CurrentHealthElement.size());
    if (currentHealthNode == nullptr)
    {
        return false;
    }

    return XmlHelper::TryGetFloat(currentHealthNode, currentHealth);
}

float StationExToolbox::DynamicThingSaveData::GetCurrentHealth() const
{
    float currentHealth;
    if (this->TryGetCurrentHealth(currentHealth))
    {
        return currentHealth;
    }

    throw std::runtime_error("Failed to read DynamicThingSaveData HealthCurrent because the element is missing or improperly formatted.");
}
