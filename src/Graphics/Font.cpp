#include <Graphics/Font.hpp>

#include <iostream>
#include <algorithm>

#define ATLAS_INITIAL_SIZE_X 1024
#define ATLAS_INITIAL_SIZE_Y 1024
#define ATLAS_MAX_SIZE_Y 8192

namespace Graphics {

	Font::Font(void) :
		m_AtlasTextureNeedsUpdate(false),
		m_CurrentX(0),
		m_CurrentY(0),
		m_NextY(0) {
		FT_Init_FreeType(&m_Library);
	}

	Font::~Font(void) {
		FT_Done_FreeType(m_Library);
	}


	bool Font::loadFromFile(const std::string& _filename, unsigned int _fontSize) {
		FT_Error newFaceError = FT_New_Face(m_Library, _filename.c_str(), 0, &m_Face);

		if (newFaceError != 0) {
			std::cerr << "Failed to create new font face: " << newFaceError << std::endl;
			return false;
		}

		FT_Error setPixelError = FT_Set_Pixel_Sizes(m_Face, 0, _fontSize);

		if (setPixelError != 0) {
			std::cerr << "Failed to set pixel size: " << setPixelError << std::endl;
			return false;
		}

		m_AtlasImage.create(ATLAS_INITIAL_SIZE_X, ATLAS_INITIAL_SIZE_Y, Colour::Blue);

		return true;
	}

	std::vector<float> Font::getVertexData(int _character, const System::Vector2f& _penPosition) {
		Glyph g = getGlyph(_character);

		if (g.character == -1) {
			return std::vector<float>();
		}
		std::vector<float> verticies;

		//~ Bottom Left
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX));					verticies.push_back(static_cast<float>(g.textureY + g.height));

		//~ Bottom Right
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + g.width));		verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX + g.width));			verticies.push_back(static_cast<float>(g.textureY + g.height));

		//~ Top Right
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + g.width));		verticies.push_back(static_cast<float>(_penPosition.y + g.height));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX + g.width));			verticies.push_back(static_cast<float>(g.textureY));



		//~ Bottom Left
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + 0.0f));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX));					verticies.push_back(static_cast<float>(g.textureY + g.height));

		//~ Top Right
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + g.width));		verticies.push_back(static_cast<float>(_penPosition.y + g.height));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX + g.width));			verticies.push_back(static_cast<float>(g.textureY));

		//~ Top Left
		//~ Position
		verticies.push_back(static_cast<float>(_penPosition.x + 0.0f));			verticies.push_back(static_cast<float>(_penPosition.y + g.height));
		//~ Texture
		verticies.push_back(static_cast<float>(g.textureX));					verticies.push_back(static_cast<float>(g.textureY));


		return verticies;
	}

	Image& Font::getAtlas(void) {
		return m_AtlasImage;
	}

	Texture& Font::getTextureAtlas(void) {
		return m_AtlasTexture;
	}
	
	void Font::preloadAtlas(const std::string& _text) {
		for (auto& c : _text) {
			addGlyphToAtlas(c, m_AtlasImage);
		}
	}

	FT_UInt Font::getGlyphIndex(int _character) {
		return FT_Get_Char_Index(m_Face, _character);
	}

	FT_GlyphSlot Font::getGlyph(FT_UInt _glyphIndex) {
		FT_Error error = FT_Load_Glyph(m_Face, _glyphIndex, FT_LOAD_RENDER);
		if (error != 0) {
			std::cerr << "Failed to load glyph: " << error << std::endl;
		}

		return m_Face->glyph;
	}

	bool Font::addGlyphToAtlas(int _character, Image& _atlas) {
		FT_GlyphSlot glyph = getGlyph(getGlyphIndex(_character));

		if (m_CurrentX + glyph->bitmap.width + 1 >= _atlas.getSize().x) {
			m_CurrentY = m_NextY;
			m_CurrentX = 0;
		}

		if (m_CurrentY + glyph->bitmap.rows >= _atlas.getSize().y) {
			if (_atlas.getSize().y >= ATLAS_MAX_SIZE_Y) {
				std::cerr << "Texture atlas too big, cannot expand." << std::endl;
				return false;
			}

			_atlas.expandVertically(_atlas.getSize().y, Colour::Magenta);
		}

		m_Glyphs.push_back(Glyph());
		m_Glyphs.back().character = _character;
		m_Glyphs.back().width = glyph->bitmap.width;
		m_Glyphs.back().height = glyph->bitmap.rows;
		m_Glyphs.back().textureX = m_CurrentX;
		m_Glyphs.back().textureY = m_CurrentY;

		for (unsigned int y = 0; y < glyph->bitmap.rows; y += 1) {
			for (unsigned int x = 0; x < glyph->bitmap.width; x += 1) {
				unsigned int atlasPosX = m_CurrentX + x;
				unsigned int atlasPosY = m_CurrentY + y;
				auto pixCol = Colour(static_cast<float>(glyph->bitmap.buffer[y * glyph->bitmap.width + x]) / 255.0f, 0.0f, 0.0f);
				_atlas.setPixel(atlasPosX, atlasPosY, pixCol);
			}
		}

		m_NextY = std::max(m_NextY, m_CurrentY + glyph->bitmap.rows + 1);
		m_CurrentX += glyph->bitmap.width + 1;

		m_AtlasTextureNeedsUpdate = true;

		return true;
	}

	Glyph Font::getGlyph(int _character) {
		for (Glyph glyph : m_Glyphs) {
			if (_character == glyph.character) {
				return glyph;
			}
		}

		if (addGlyphToAtlas(_character, m_AtlasImage)) {
			return getGlyph(_character);
		}
		else {
			Glyph g = Glyph();

			g.character = -1;

			return g;
		}
	}

	void Font::updateTextureIfNeeded(void) {
		if (m_AtlasTextureNeedsUpdate) {
			m_AtlasTextureNeedsUpdate = false;

			m_AtlasTexture.loadFromImage(m_AtlasImage);

			m_AtlasTexture.setWrapMode(Texture::TextureWrap::CLAMP, Texture::TextureWrap::CLAMP);
		}
	}

	FT_Vector Font::getKerning(int _previous, int _current) {
		FT_Vector kerning;

		FT_Get_Kerning(m_Face, getGlyphIndex(_previous), getGlyphIndex(_current), FT_KERNING_DEFAULT, &kerning);

		return kerning;
	}
}