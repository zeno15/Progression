#include <Graphics/Text.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Window/OpenGL.hpp>

#include <algorithm>

namespace Graphics {
	Text::Text(void) :
		m_Font(nullptr),
		m_Verticies(0),
		m_UseKerning(true),
		m_Colour(Colour::White) {

	}

	Text::~Text(void) {
		//glDeleteVertexArrays(1, &m_VAO);
		//glDeleteBuffers(1, &m_VBO);

	}


	void Text::render(const Window::Window& _window, RenderData _RenderData) const {
		if (m_Font == nullptr) {
			return;
		}

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(Infrastructure::ShaderManager::TextShaderName);

		shader.bind();
		shader.passUniform(Infrastructure::ShaderManager::TextShaderMVPName, _RenderData.view * _RenderData.projection * _RenderData.model);
		shader.passUniform(Infrastructure::ShaderManager::TextShaderTexSizeName, m_Font->getTextureAtlas().getSize());
		shader.passUniform(Infrastructure::ShaderManager::TextShaderColourName, m_Colour);
		
		m_Font->getTextureAtlas().bind();

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_Verticies);
	}
	void Text::generateText(const std::string& _text, Font *_font) {
		if (_font == nullptr) {
			return;
		}

		if (_text == m_Text && _font == m_Font) {
			return;
		}

		m_Text = _text;
		m_Font = _font;
		
		glDeleteVertexArrays(1, &m_VAO);

		std::vector<float> data;

		System::Vector2f penPos = m_Position;

		float top = 0.0f;
		float bottom = std::numeric_limits<float>().max();
		float left = std::numeric_limits<float>().max();
		float right = 0.0f;

		for (unsigned int i = 0; i < _text.size(); i += 1) {
			FT_UInt index = m_Font->getGlyphIndex(static_cast<int>(_text.at(i)));

			System::Vector2f kerning;

			if (m_UseKerning && i > 0) {
				FT_Vector k = m_Font->getKerning(_text.at(i - 1), _text.at(i));
				kerning.x = static_cast<float>(k.x >> 6);
			}

			FT_GlyphSlot glyph = m_Font->getGlyph(index);

			std::vector<float> verts = m_Font->getVertexData(static_cast<int>(_text.at(i)), penPos + System::Vector2f(static_cast<float>(glyph->bitmap_left + kerning.x), static_cast<float>(glyph->bitmap_top) - static_cast<float>(glyph->bitmap.rows)));

			for (unsigned int j = 0; j < verts.size(); j += 4) {
				data.push_back(verts.at(j + 0));	//~ x pos
				data.push_back(verts.at(j + 1));	//~ y pos
				data.push_back(verts.at(j + 2));	//~ x tex
				data.push_back(verts.at(j + 3));	//~ y tex

				top = std::max(top, verts.at(j + 1));
				bottom = std::min(bottom, verts.at(j + 1));

				left = std::min(left, verts.at(j));
				right = std::max(right, verts.at(j));
			}

			penPos.x += glyph->advance.x >> 6;
		}


		m_Verticies = (data.size() / 4);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(2 * sizeof(float)));

		
		m_Font->updateTextureIfNeeded();
	}
	void Text::setColour(const Colour& _colour) {
		m_Colour = _colour;
	}
	void Text::setPosition(const System::Vector2f& _position) {
		m_Position = _position;
	}
}