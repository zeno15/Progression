#ifndef INCLUDED_UTILITY_STRING_HELPER_HPP_
#define INCLUDED_UTILITY_STRING_HELPER_HPP_

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

////////////////////////////////////////////////////////////
///
///	\namespace	Utility
///
////////////////////////////////////////////////////////////
namespace Utility {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to provide helper string methods
	///
	////////////////////////////////////////////////////////////
	class StringHelper {
	public:
		////////////////////////////////////////////////////////////
		///
		/// \brief  Splits a string by a given delimiter string
		///
		/// \param  _string         String to be split
		///
		/// \param  _splitString    Delimiter string
		///
		/// \return Vector of String's that consists of \a _string
		///         split by \a _splitString
		///
		////////////////////////////////////////////////////////////
		static std::vector<std::string> splitStringByString(const std::string& _string, const std::string& _splitString);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Splits a string by a set of given delimiters
		///
		/// \param  _string String to be split
		///
		/// \param  _splitStrings   Vector of delimiter strings
		///
		/// \return Vector of String's that consists of \a _string
		///         split by each String in \a _splitStrings
		///
		////////////////////////////////////////////////////////////
		static std::vector<std::string> splitStringByDelimeters(const std::string& _string, const std::vector<std::string>& _splitStrings);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether a string starts with another
		///
		///	\param	_str	String that may begin with another
		///
		///	\param	_start	The other string to check
		///
		///	\return	Whether \a _str starts with \a _start
		///
		////////////////////////////////////////////////////////////
		static bool startsWith(const std::string& _str, const std::string& _start);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets whether a string ends with another
		///
		///	\param	_str	String that may end with another
		///
		///	\param	_end	The other string to check
		///
		///	\return	Whether \a _str ends with \a _end
		///
		////////////////////////////////////////////////////////////
		static bool endsWith(const std::string& _str, const std::string& _end);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Strips all whitespace from a string
		///
		///	\param	_str	The string to remove whitespace from
		///
		///	\return	\a _str without any whitespace
		///
		////////////////////////////////////////////////////////////
		static std::string stripWhitespace(const std::string& _str);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Replaces all occurences of a string with another
		///
		///	\param	_string			The string to modify
		///
		///	\param	_substring		The string to replace
		///
		///	\param	_replacement	The string to insert
		///
		////////////////////////////////////////////////////////////
		static void replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Trims whitespace from the left of a string
		///
		///	\param	_s	The string to remove whitespace from
		///
		///	\return	\_s without any left whitespace
		///
		////////////////////////////////////////////////////////////
		static std::string &ltrim(std::string &_s);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Trims whitespace from the right of a string
		///
		///	\param	_s	The string to remove whitespace from
		///
		///	\return	\_s without any right whitespace
		///
		////////////////////////////////////////////////////////////
		static std::string &rtrim(std::string &s);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Trims whitespace from both ends of a string
		///
		///	\param	_s	The string to remove whitespace from
		///
		///	\return	\_s without any leading or trailing whitespace
		///
		////////////////////////////////////////////////////////////
		static std::string &trim(std::string &s);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Compares two strings in a non case sensitive manner
		///
		///	\param	_left	The first string to compare
		///
		///	\param	_right	The second string to compare
		///
		///	\return	Whether \a _left and \a _right are the same 
		///			irrelevant of case
		///
		////////////////////////////////////////////////////////////
		static bool compareCaseInsensitive(const std::string& _left, const std::string& _right);

	};
}

#endif //INCLUDED_UTILITY_STRING_HELPER_HPP_