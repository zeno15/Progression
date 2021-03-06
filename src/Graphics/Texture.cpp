#include <Graphics/Texture.hpp>

#include <Window/OpenGL.hpp>

namespace Graphics {
	static const int wrapModes[3] = { 
		GL_CLAMP_TO_EDGE, 
		GL_REPEAT, 
		GL_MIRRORED_REPEAT 
	};

	Texture::Texture(void) :
		m_TextureHandle(0),
		m_XAxisWrap(TextureWrap::CLAMP),
		m_YAxisWrap(TextureWrap::CLAMP) {
	}

	Texture::~Texture(void) {
	}


	bool Texture::loadFromFile(const std::string& _filename) {
		Image image;
		if (!image.loadFromFile(_filename)) {
			return false;
		}

		return loadFromImage(image);
	}

	bool Texture::loadFromImage(const Image& _image) {
		//~ Deletes the texture if it exists
		glDeleteTextures(1, &m_TextureHandle);

		m_PixelData.resize(_image.getSize().x * _image.getSize().y * 4);

		//~ Flips around x-axis as opengl origin is bottom left
		for (unsigned int y = 0; y < _image.getSize().y; y += 1) {
			for (unsigned int x = 0; x < _image.getSize().x; x += 1) {
				Colour col = _image.getPixel(x, _image.getSize().y - y - 1);

				m_PixelData.at((y * _image.getSize().x + x) * 4 + 0) = static_cast<uint8_t>(255.0f * col.r);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 1) = static_cast<uint8_t>(255.0f * col.g);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 2) = static_cast<uint8_t>(255.0f * col.b);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 3) = static_cast<uint8_t>(255.0f * col.a);
			}
		}

		m_Size = _image.getSize();

		glGenTextures(1, &m_TextureHandle);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_PixelData.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModes[m_XAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModes[m_YAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		return true;
	}

	void Texture::bind(void) const {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		glUniform1i(m_TextureHandle, 0);
	}
	void Texture::unbind(void) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	System::Vector2<unsigned int> Texture::getSize(void) const {
		return m_Size;
	}

	void Texture::setWrapMode(TextureWrap _xAxis, TextureWrap _yAxis) {
		m_XAxisWrap = _xAxis;
		m_YAxisWrap = _yAxis;

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModes[m_XAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModes[m_YAxisWrap]);
	}
}