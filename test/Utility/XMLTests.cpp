#include <catch.hpp>

#include <Utility/StringHelper.hpp>
#include <Utility/XML.hpp>

namespace Utility {
	namespace tests {
		const std::string basic = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<Root>
</Root>)";

		const std::string basicAttributes = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<Root>
	<Child1 Attribute="Value"/>
	<Child2 Attribute2='Value2'>
		<Child3 />
	</Child2>
</Root>)";

		TEST_CASE("Basic single root node no children is parsed correctly.", "[XML]") {
			XML xml = XML();

			REQUIRE(xml.createTree(basic));

			REQUIRE(xml.getRoot()->m_Nodes.size() == 2);
			REQUIRE(xml.getRoot()->m_Nodes[0]->m_Type == XML::DECLARATION);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Type == XML::ELEMENT);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Tag == "Root");
		}

		TEST_CASE("Children with attributes", "[XML]") {
			XML xml = XML();

			REQUIRE(xml.createTree(basicAttributes));
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes.size() == 2);

			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[0]->m_Type == XML::CLOSED_ELEMENT);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[0]->m_Tag == "Child1");
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[0]->m_AttributePairs.size() == 1);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[0]->m_AttributePairs[0].first == "Attribute");
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[0]->m_AttributePairs[0].second == "Value");

			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[1]->m_Type == XML::ELEMENT);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[1]->m_Tag == "Child2");
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[1]->m_AttributePairs.size() == 1);
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[1]->m_AttributePairs[0].first == "Attribute2");
			REQUIRE(xml.getRoot()->m_Nodes[1]->m_Nodes[1]->m_AttributePairs[0].second == "Value2");
		}
	}
}