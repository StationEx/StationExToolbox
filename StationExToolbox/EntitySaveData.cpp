#include "EntitySaveData.h"

#include <stdexcept>
#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view StateElement = "State"sv;

static constexpr StationExToolbox::EntityState ConvertTextToEntityState(const std::string_view state) noexcept
{
	if (state == "Alive")
	{
		return StationExToolbox::EntityState::Alive;
	}
	else if (state == "Dead")
	{
		return StationExToolbox::EntityState::Dead;
	}
	else if (state == "Unconscious")
	{
		return StationExToolbox::EntityState::Unconscious;
	}
	else if (state == "Decay")
	{
		return StationExToolbox::EntityState::Decayed;
	}
	else
	{
		return StationExToolbox::EntityState::Unknown;
	}
}

bool StationExToolbox::EntitySaveData::TryGetState(EntityState& state) const noexcept
{
	const XmlNode* const stateNode = this->root->first_node(StateElement.data(), StateElement.size());
	if (stateNode == nullptr)
	{
		return false;
	}

	return ConvertTextToEntityState(std::string_view(stateNode->value(), stateNode->value_size()));
}

StationExToolbox::EntityState StationExToolbox::EntitySaveData::GetState() const
{
	EntityState state;
	if (this->TryGetState(state))
	{
		return state;
	}

	throw std::runtime_error("Failed to read EntitySaveData State because the element is missing or improperly formatted.");
}
