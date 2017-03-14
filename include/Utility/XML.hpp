#ifndef INCLUDED_UTILITY_XML_HPP_
#define INCLUDED_UTILITY_XML_HPP_

#include <string>
#include <vector>

////////////////////////////////////////////////////////////
///
///	\namespace	Utility
///
////////////////////////////////////////////////////////////
namespace Utility {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to encapsulate XML parsing and creating
	///
	////////////////////////////////////////////////////////////
	class XML {
	public:
		enum NodeType {
			DECLARATION,
			COMMENT,
			CONTENT,
			ELEMENT,
			CLOSED_ELEMENT,
			ROOT
		};

		static const std::string DeclarationStart;				///<	'<?'
		static const std::string DeclarationEnd;				///<	'?>'
		static const std::string CommentStart;					///<	'<!--'
		static const std::string CommentEnd;					///<	'-->'
		static const std::string ClosedElementStart;			///<	'<'
		static const std::string ClosedElementEnd;				///<	'/>'
		static const std::string SelfClosingElementStart;		///<	'</'
		static const std::string ElementStart;					///<	'<'
		static const std::string ElementEnd;					///<	'>'
		static const std::string Space;							///<	' '
		static const std::string Equals;						///<	'='

		////////////////////////////////////////////////////////////
		///
		///	\brief	Class to represent a single XML node.
		///
		////////////////////////////////////////////////////////////
		class XMLNode {
		public:

			////////////////////////////////////////////////////////////
			///
			///	\brief	Recursively clears the node and its children
			///
			////////////////////////////////////////////////////////////
			void clear(void);

			////////////////////////////////////////////////////////////
			///
			///	\brief	Recursively creates a tree from the given data
			///
			///	\param	The data to make the sub tree from
			///
			///	\return	Whether the tree was created successfully
			///
			////////////////////////////////////////////////////////////
			bool create(const std::string& _data);

		public:
			NodeType                    m_Type;										///<	Node type

			std::string                 m_Tag;										///<	Name of node tag
			std::string                 m_Content;									///<	Content of node
			std::vector<XMLNode *>      m_Nodes;									///<	Vector of child nodes

			std::vector<std::pair<std::string, std::string>>    m_AttributePairs;	///<	Vector of attribute value pairs
		};

	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Creates an XML tree from data from a file
		///
		///	\param	The filename to load
		///
		///	\return	Whether the file was loaded and tree created successfully
		///
		////////////////////////////////////////////////////////////
		bool loadFromFile(const std::string& _filename);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Create an XML tree from a string
		///
		///	\param	The data
		///
		///	\return Whether the tree was created successfully
		///
		////////////////////////////////////////////////////////////
		bool loadFromString(const std::string& _data);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Create an XML tree from a string
		///
		///	\param	The data
		///
		///	\return Whether the tree was created successfully
		///
		////////////////////////////////////////////////////////////
		bool createTree(const std::string& _data);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the root node
		///
		///	\return	The root node
		///
		////////////////////////////////////////////////////////////
		XMLNode *getRoot(void);

	private:
		static bool extractFromBetweenTag(const std::string& _tag, std::string& _extracted, std::string& _data);

		static bool extractAttributesFromElement(const std::string& _element, XMLNode *node);

	private:
		XMLNode     m_Root;			///<	The root node.
	};
}

#endif // INCLUDED_UTILITY_XML_HPP_