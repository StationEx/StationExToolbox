#pragma once

#include "XmlHelper.h"

#include <filesystem>
#include <memory>

namespace StationExToolbox
{
	class WorldXmlDocument
	{
		private:
		std::unique_ptr<char[]> content;
		std::unique_ptr<XmlDocument> document;

		public:
		[[nodiscard]]
		static WorldXmlDocument FromFile(std::filesystem::path path);

		inline WorldXmlDocument(std::unique_ptr<char[]> content, std::unique_ptr<XmlDocument> document) noexcept
			: content(std::move(content)),
			document(std::move(document))
		{

		}

		inline WorldXmlDocument(WorldXmlDocument&& other) noexcept
			: content(std::move(other.content)),
			document(std::move(other.document))
		{

		}

		WorldXmlDocument(WorldXmlDocument&) = delete;
		~WorldXmlDocument() noexcept = default;

		inline WorldXmlDocument& operator =(WorldXmlDocument&& other) noexcept
		{
			if (this != &other)
			{
				this->document = std::move(other.document);
			}

			return *this;
		}

		inline WorldXmlDocument& operator =(const WorldXmlDocument&) = delete;

		[[nodiscard]]
		XmlNode* TryGetAllThingsElement() const noexcept;
	};
}
