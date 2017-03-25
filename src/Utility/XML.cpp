#include <Utility/XML.hpp>

#include <Utility/StringHelper.hpp>

#include <fstream>
#include <iostream>

namespace Utility {
	const std::string XML::DeclarationStart = "<?";
	const std::string XML::DeclarationEnd = "?>";
	const std::string XML::CommentStart = "<!--";
	const std::string XML::CommentEnd = "-->";
	const std::string XML::ClosedElementStart = "<";
	const std::string XML::ClosedElementEnd = "/>";
	const std::string XML::SelfClosingElementStart = "</";
	const std::string XML::ElementStart = "<";
	const std::string XML::ElementEnd = ">";
	const std::string XML::Space = " ";
	const std::string XML::Equals = "=";

	void XML::XMLNode::clear(void) {
		for (XMLNode *node : m_Nodes) {
			node->clear();

			delete node;
		}

		m_Nodes.clear();
	}

	bool XML::XMLNode::create(const std::string& _data) {
		std::string data = _data;

		while (_data.size()) {
			std::size_t startLoc = data.find(ElementStart);
			std::size_t closeLoc = data.find(ElementEnd);

			if (startLoc == std::string::npos) {
				// Either _data is pure content, or an error has occured
				// Assume content

				data = StringHelper::trim(data);

				if (data.size()) {
					XMLNode *node = new XMLNode();

					node->m_Type = NodeType::CONTENT;
					node->m_Content = data;

					m_Nodes.push_back(node);
				}

				return true;
			}

			if (closeLoc == std::string::npos) {
				std::cerr << "Found close > without open <: poorly formatted xml" << std::endl;
				return false;
			}
			std::string element = data.substr(startLoc, closeLoc - startLoc + 1);

			if (StringHelper::startsWith(element, DeclarationStart) && StringHelper::endsWith(element, DeclarationEnd)) {
				// TODO extract declaration from element

				XMLNode *node = new XMLNode();

				node->m_Type = NodeType::DECLARATION;
				node->m_Content = element;

				m_Nodes.push_back(node);
				data = data.substr(data.find(ElementStart, closeLoc), std::string::npos);
			}
			else if (StringHelper::startsWith(element, CommentStart) && StringHelper::endsWith(element, CommentEnd)) {
				// TODO extract comment from element

				XMLNode *node = new XMLNode();

				node->m_Type = NodeType::COMMENT;
				node->m_Content = element;

				m_Nodes.push_back(node);
				data = data.substr(data.find(ElementStart, closeLoc), std::string::npos);
			}
			else if (StringHelper::startsWith(element, ClosedElementStart) && StringHelper::endsWith(element, ClosedElementEnd)) {
				std::size_t startLocation = data.find(ElementStart, closeLoc);

				// If you cant find a tag start '<' then the data can be replaced with an empty string, no more content/tags
				data = (startLocation == std::string::npos) ? "" : data.substr(startLocation, std::string::npos);


				std::size_t loc = element.find_first_of("> "); // TODO: Why the space?
				std::string tag = element.substr(1, loc - 1);

				XMLNode *node = new XMLNode();

				node->m_Tag = tag;
				node->m_Type = NodeType::CLOSED_ELEMENT;

				if (!extractAttributesFromElement(element, node)) {
					std::cout << "Closed element failed to extract attributes" << std::endl;
					return false;
				}

				m_Nodes.push_back(node);
			}
			else {
				std::size_t loc = element.find_first_of("> "); // TODO: Why the space?
				std::string tag = element.substr(1, loc - 1);

				std::string extracted;

				if (!extractFromBetweenTag(tag, extracted, data)) {
					std::cerr << "Could not extract data from between the '<" << tag << ">' tag." << std::endl;

					return false;
				}
				else {
					XMLNode *node = new XMLNode();

					if (!node->create(extracted)) {
						return false;
					}

					node->m_Tag = tag;
					node->m_Type = NodeType::ELEMENT;

					if (!extractAttributesFromElement(element, node)) {
						std::cerr << "Element failed to extract attributes" << std::endl;

						delete node;

						return false;
					}

					m_Nodes.push_back(node);
				}
			}
		}

		return true;
	}

	bool XML::loadFromFile(const std::string& _filename) {
		std::ifstream file;
		file.open(_filename);

		if (!file.good()) {
			std::cerr << "Failed to load XML file: " << _filename << std::endl;
			return false;
		}

		std::string str;

		file.seekg(0, std::ios::end);
		str.reserve(static_cast<unsigned int>(file.tellg()));
		file.seekg(0, std::ios::beg);

		str.insert(str.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

		bool outcome = loadFromString(str);

		if (!outcome) {
			std::cerr << "Failed to build xml tree." << std::endl;
		}

		file.close();

		return outcome;
	}

	bool XML::loadFromString(const std::string& _data) {
		return createTree(_data);
	}
	
	bool XML::createTree(const std::string& _data) {
		m_Root.clear();

		bool val = m_Root.create(_data);

		m_Root.m_Type = NodeType::ROOT;

		return val;
	}

	XML::XMLNode *XML::getRoot(void) {
		return &m_Root;
	}

	bool XML::extractFromBetweenTag(const std::string& _tag, std::string& _extracted, std::string& _data) {
		std::size_t loc = _data.find(std::string(ElementStart + _tag));

		if (loc == std::string::npos) {
			return false;
		}

		std::size_t nextTagLoc = _data.find(ElementStart, loc + _tag.size());

		if (nextTagLoc == _data.find(std::string(SelfClosingElementStart + _tag + ElementEnd))) {

			std::size_t openEnd = _data.find(ElementEnd);
			std::size_t closeStart = _data.find(SelfClosingElementStart);

			_extracted = _data.substr(openEnd + 1, closeStart - openEnd - 1);
		}
		else {
			_extracted = _data.substr(nextTagLoc, std::string::npos);

			_extracted = _extracted.substr(0, _extracted.find(std::string(SelfClosingElementStart + _tag + ElementEnd)));
		}

		_data = _data.substr(_data.find(std::string(SelfClosingElementStart + _tag + ElementEnd)) + 3 + _tag.size(), std::string::npos);

		return true;
	}

	bool XML::extractAttributesFromElement(const std::string& _element, XMLNode *node) {
		std::string element(_element);

		std::size_t equalLoc = element.find(Equals);

		while (equalLoc != std::string::npos) {
			std::size_t attribStart = element.find_last_of(Space, equalLoc);

			std::string attrib = element.substr(attribStart + 1, equalLoc - attribStart - 1);

			std::size_t endValueLoc = element.find(element[equalLoc + 1], equalLoc + 2);

			std::string value = element.substr(equalLoc + 2, endValueLoc - equalLoc - 2);

			element = element.substr(endValueLoc, std::string::npos);

			node->m_AttributePairs.push_back(std::pair<std::string, std::string>(attrib, value));

			equalLoc = element.find(Equals);
		}

		return true;
	}
}