#pragma once

#include "ThingSaveData.h"

#include <string_view>

using namespace std::string_view_literals;

static constexpr std::string_view Element = "ThingSaveData"sv;
static constexpr std::string_view ReferenceIdElement = "ReferenceId"sv;
static constexpr std::string_view PrefabNameElement = "PrefabName"sv;

bool StationExToolbox::ThingSaveData::TryGetReferenceId(std::uint64_t& referenceId) const noexcept
{
	const XmlNode* const referenceIdNode = XmlHelper::TryGetElementByName(this->root, ReferenceIdElement);
	if (referenceIdNode == nullptr)
	{
		return false;
	}

	return XmlHelper::TryGetUInt64(referenceIdNode, referenceId);
}

bool StationExToolbox::ThingSaveData::TryGetPrefabName(std::string_view& prefabName) const noexcept
{
	const XmlNode* const prefabNameNode = XmlHelper::TryGetElementByName(this->root, PrefabNameElement);
	if (prefabNameNode == nullptr)
	{
		return false;
	}

	prefabName = std::string_view(prefabNameNode->value(), prefabNameNode->value_size());
	return true;
}