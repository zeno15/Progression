#include <Utility/StringHelper.hpp>

#include <iostream>

namespace Utility {

	std::vector<std::string> StringHelper::splitStringByString(const std::string& _string, const std::string& _splitString) {
		std::vector<std::string> returnValue;
		std::string string(_string);
		std::size_t loc;
		std::size_t splitStringLength = _splitString.size();

		while (std::string::npos != (loc = string.find(_splitString))) {
			std::string pre = string.substr(0, loc);

			string = string.substr(loc + splitStringLength, std::string::npos);

			if (pre.size() > 0) {
				returnValue.push_back(pre);
			}
		}

		return returnValue;
	}

	std::vector<std::string> StringHelper::splitStringByDelimeters(const std::string& _string, const std::vector<std::string>& _splitStrings) {
		std::vector<std::string> returnValue;
		std::string string(_string);

		while (true) {
			std::size_t closestDelimiter = std::string::npos;
			std::size_t closestDelimiterSize;
			for (auto& delimeter : _splitStrings) {
				auto pos = string.find(delimeter);
				if (pos != std::string::npos && pos >= 0 && pos < closestDelimiter) {
					closestDelimiter = pos;
					closestDelimiterSize = delimeter.size();
				}
			}
			if (closestDelimiter == std::string::npos) {
				if (string.size() > 0) {
					returnValue.push_back(string);
				}
				break;
			}
			std::string pre = string.substr(0, closestDelimiter);

			string = string.substr(closestDelimiter + closestDelimiterSize, std::string::npos);

			if (pre.size() > 0) {
				returnValue.push_back(pre);
			}
		}

		return returnValue;
	}

	bool StringHelper::startsWith(const std::string& _str, const std::string& _start) {
		return (_str.find(_start) == 0);
	}

	bool StringHelper::endsWith(const std::string& _str, const std::string& _end) {
		return (_str.find(_end) == _str.size() - _end.size());
	}

	std::string StringHelper::stripWhitespace(const std::string& _str) {
		std::string str(_str);

		if (!_str.size()) {
			return str;
		}

		const std::string whitespace(" \n\r\t");

		while (str.find_first_of(whitespace) == 0) {
			str = str.substr(1, std::string::npos);
		}

		return str;
	}

	void StringHelper::replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement) {
		std::size_t pos = 0;
		while ((pos = _string.find(_substring, pos)) != std::string::npos) {
			_string.replace(pos, _substring.size(), _replacement);

			pos += _replacement.size();
		}
	}

	std::string &StringHelper::ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	std::string &StringHelper::rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	std::string &StringHelper::trim(std::string &s) {
		return ltrim(rtrim(s));
	}

	bool StringHelper::compareCaseInsensitive(const std::string& _left, const std::string& _right) {
		if (_left.length() == _right.length()) {
			return std::equal(_left.begin(), _left.end(), _right.begin(), [](char _a, char _b) {
				return std::tolower(_a) == std::tolower(_b);
			});
		}

		return false;
	}
}