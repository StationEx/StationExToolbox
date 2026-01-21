#pragma once

#include "Human.h"
#include "Error.h"
#include "XmlHelper.h"

#include <charconv>
#include <expected>
#include <string>
#include <vector>

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
			return XmlHelper::TryParseContent(this->document, this->content.get());
		}

		[[nodiscard]]
		Error GetHumans(std::vector<Human>& humans) const noexcept;

		[[nodiscard]]
		Error GetHumanByReferenceId(const std::uint64_t referenceId, Human& entity) const noexcept;
	};
}
