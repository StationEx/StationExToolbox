#pragma once

#include <charconv>
#include <expected>
#include <string>

#include "rapidxml/rapidxml.h"
#include "rapidxml/rapidxml_utils.h"

#include "WorldData.h"
#include "Things.h"
#include "Human.h"
#include "Error.h"

using XmlFile = rapidxml::file<char>;
using XmlDocument = rapidxml::xml_document<char>;
using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

namespace StationExToolbox
{
	class WorldXmlDocument
	{
		private:
		XmlFile file;
		XmlDocument document;

		[[nodiscard]]
		inline XmlNode* GetThingContainerNode() const
		{
			XmlNode* worldDataNode = this->document.first_node(WorldData::Element.data(), WorldData::Element.size());
			if (worldDataNode == nullptr)
			{
				return nullptr;
			}

			return worldDataNode->first_node(Things::Element.data(), Things::Element.size());
		}

		public:
		inline WorldXmlDocument(const std::string& path)
			: file(path.c_str())
		{
			this->Reset();
		}

		inline void Reset()
		{
			this->document.parse<rapidxml::parse_non_destructive>(this->file.data());
		}

		[[nodiscard]]
		std::expected<Human, Error> GetHumanById(const std::uint64_t referenceId) const;
	};
}
