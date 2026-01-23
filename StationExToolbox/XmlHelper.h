#pragma once

#include <charconv>
#include <cstdint>

#include "Vector3.h"
#include "Quaternion.h"

#include <rapidxml/rapidxml.h>

using XmlDocument = rapidxml::xml_document<char>;
using XmlNode = rapidxml::xml_node<char>;
using XmlAttribute = rapidxml::xml_attribute<char>;

namespace StationExToolbox
{
	class XmlHelper
	{
		public:
		[[nodiscard]]
		static inline bool TryParseContent(XmlDocument& document, char const* const content) noexcept
		{
			try
			{
				document.parse<rapidxml::parse_non_destructive>(const_cast<char*>(content));
			}
			catch (...)
			{
				return false;
			}

			return true;
		}

		static inline bool TryGetUInt32(const XmlNode* const node, std::uint32_t& value) noexcept
		{
			const char* const nodeValueEnd = node->value() + node->value_size();
			auto [ptr, ec] = std::from_chars(node->value(), nodeValueEnd, value);

			return (ec == std::errc() && ptr == nodeValueEnd);
		}

		[[nodiscard]]
		static inline bool TryGetUInt64(const XmlNode* const node, std::uint64_t& value) noexcept
		{
			const char* const nodeValueEnd = node->value() + node->value_size();
			auto [ptr, ec] = std::from_chars(node->value(), nodeValueEnd, value);

			return (ec == std::errc() && ptr == nodeValueEnd);
		}

		[[nodiscard]]
		static inline bool TryGetFloat(const XmlNode* const node, float& value) noexcept
		{
			const char* const nodeValueEnd = node->value() + node->value_size();
			auto [ptr, ec] = std::from_chars(node->value(), nodeValueEnd, value);

			return (ec == std::errc() && ptr == nodeValueEnd);
		}

		[[nodiscard]]
		static inline bool TryGetVector3(const XmlNode* const node, Vector3& value) noexcept
		{
			const XmlNode* const xNode = node->first_node(Vector3::XElement.data(), Vector3::XElement.size());
			if (xNode == nullptr || !TryGetFloat(xNode, value.X))
			{
				return false;
			}

			const XmlNode* const yNode = node->first_node(Vector3::YElement.data(), Vector3::YElement.size());
			if (yNode == nullptr || !TryGetFloat(yNode, value.Y))
			{
				return false;
			}

			const XmlNode* const zNode = node->first_node(Vector3::ZElement.data(), Vector3::ZElement.size());
			if (zNode == nullptr || !TryGetFloat(zNode, value.Z))
			{
				return false;
			}

			return true;
		}

		[[nodiscard]]
		static inline bool TryGetQuaternion(const XmlNode* const node, Quaternion& value) noexcept
		{
			const XmlNode* const xNode = node->first_node(Quaternion::XElement.data(), Quaternion::XElement.size());
			if (xNode == nullptr || !TryGetFloat(xNode, value.X))
			{
				return false;
			}

			const XmlNode* const yNode = node->first_node(Quaternion::YElement.data(), Quaternion::YElement.size());
			if (yNode == nullptr || !TryGetFloat(yNode, value.Y))
			{
				return false;
			}

			const XmlNode* const zNode = node->first_node(Quaternion::ZElement.data(), Quaternion::ZElement.size());
			if (zNode == nullptr || !TryGetFloat(zNode, value.Z))
			{
				return false;
			}

			const XmlNode* const wNode = node->first_node(Quaternion::WElement.data(), Quaternion::WElement.size());
			if (wNode == nullptr || !TryGetFloat(wNode, value.W))
			{
				return false;
			}

			return true;
		}
	};
}