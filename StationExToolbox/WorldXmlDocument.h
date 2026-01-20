#pragma once

#include "Human.h"
#include "Error.h"

#include "rapidxml/rapidxml.h"

#include <charconv>
#include <expected>
#include <string>
#include <vector>

using XmlDocument = rapidxml::xml_document<char>;

namespace StationExToolbox
{
	class WorldXmlDocument
	{
		private:
		std::unique_ptr<char[]> content;
		XmlDocument document;

		public:
		inline WorldXmlDocument(std::unique_ptr<char[]> content) noexcept
			: content(std::move(content))
		{

		}

		[[nodiscard]]
		inline bool Parse() noexcept
		{
			try
			{
				this->document.parse<rapidxml::parse_non_destructive>(this->content.get());
			}
			catch (...)
			{
				return false;
			}

			return true;
		}

		[[nodiscard]]
		Error GetHumans(std::vector<Human>& humans) const noexcept;

		[[nodiscard]]
		Error GetHumanByReferenceId(const std::uint64_t referenceId, Human& entity) const noexcept;
	};
}
