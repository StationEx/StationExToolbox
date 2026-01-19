#include "WorldXmlDocument.h"

using namespace StationExToolbox;

std::expected<Human, Error> WorldXmlDocument::GetHumanById(const std::uint64_t referenceId) const
{
	const XmlNode* const things = this->GetThingContainerNode();
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
			auto [ptr, _] = std::from_chars(referenceIdElement->value(), referenceIdElement->value() + referenceIdElement->value_size(), currentReferenceId);
			if (ptr != referenceIdElement->value() + referenceIdElement->value_size())
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

				return Human(referenceId, std::string_view(nameElement->value(), nameElement->value_size()));
			}
		}

		node = node->next_sibling(Human::Element.data(), Human::Element.size());
	}

	return std::unexpected(Error::EntityNotFound);
}