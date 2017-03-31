#include <Infrastructure/FontManager.hpp>

namespace Infrastructure {

	const std::string FontManager::Name = "FontManager";

	FontManager::FontManager() {}


	FontManager::~FontManager() {}


	void FontManager::addFont(const std::string& _filename, const std::string& _fontName) {
		if (m_Fonts.find(_fontName) == m_Fonts.end()) {
			auto t = new Graphics::Font();
			if (!t->loadFromFile(_filename, 32)) {
				throw std::runtime_error("Failed to load font");
			}

			m_Fonts.insert(std::pair<std::string, Graphics::Font *>(_fontName, t));
		}
	}

	Graphics::Font& FontManager::getFont(const std::string& _fontName) {
		if (m_Fonts.find(_fontName) != m_Fonts.end()) {
			return *m_Fonts[_fontName];
		}

		throw std::runtime_error("Failed to find font");
	}

}
