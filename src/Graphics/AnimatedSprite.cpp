#include <Graphics/AnimatedSprite.hpp>

#include <Infrastructure/InstanceCollection.hpp>
#include <Infrastructure/TextureManager.hpp>
#include <Infrastructure/ShaderManager.hpp>

#include <Driller/Scenes/DrillerGameScene.hpp>


#include <Window/OpenGL.hpp>

namespace Graphics {
	AnimatedSprite::AnimatedSprite(const std::string& _textureName) :
		m_AnimationIndex(0),
		m_VAO(0),
		m_VBO(0) {
		m_TextureName = _textureName;
		m_TextureSize = Infrastructure::InstanceCollection::getInstance<Infrastructure::TextureManager>().getTexture(_textureName).getSize();
	}

	AnimatedSprite::~AnimatedSprite(void) {

	}


	void AnimatedSprite::render(const Window::Window& _window, RenderData _renderData) const {

		auto& shader = Infrastructure::InstanceCollection::getInstance<Infrastructure::ShaderManager>().getShader(_renderData.shaderName);
		shader.bind();
		shader.passUniform("MVP", _renderData.projection * _renderData.view * _renderData.model * System::Mat4x4::createTranslation(System::Vector3f(getPosition(), 0.0f)));
		_renderData.texture->bind();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, m_AnimationIndex * 6, 6);
	}

	void AnimatedSprite::clearAnimations(void) {
		m_GraphicsData.clear();
	}
	void AnimatedSprite::addAnimation(const System::Vector2f& _spriteSize, const System::Vector2f& _textureCoords) {
		addAnimation(_spriteSize, _textureCoords, _spriteSize);
	}
	void AnimatedSprite::addAnimation(const System::Vector2f& _spriteSize, const System::Vector2f& _textureCoords, const System::Vector2f& _textureCoordSize) {
		std::vector<float> frameData = {
			// pos.x, pos.y, text.x, text.y -BL
			-_spriteSize.x / 2.0f,
			+_spriteSize.y * 1.0f,
			(_textureCoords.x + _textureCoordSize.x * 0.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 0.0f) / m_TextureSize.x,
			
			// pos.x, pos.y, text.x, text.y -BR
			+_spriteSize.x / 2.0f,
			+_spriteSize.y * 1.0f,
			(_textureCoords.x + _textureCoordSize.x * 1.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 0.0f) / m_TextureSize.y,
			
			// pos.x, pos.y, text.x, text.y -TR
			+_spriteSize.x / 2.0f,
			+_spriteSize.y * 0.0f,
			(_textureCoords.x + _textureCoordSize.x * 1.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 1.0f) / m_TextureSize.y,
			

			// pos.x, pos.y, text.x, text.y -BL
			-_spriteSize.x / 2.0f,
			+_spriteSize.y * 1.0f,
			(_textureCoords.x + _textureCoordSize.x * 0.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 0.0f) / m_TextureSize.x,
			
			// pos.x, pos.y, text.x, text.y -TR
			+_spriteSize.x / 2.0f,
			+_spriteSize.y * 0.0f,
			(_textureCoords.x + _textureCoordSize.x * 1.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 1.0f) / m_TextureSize.y,
			
			// pos.x, pos.y, text.x, text.y -TL
			-_spriteSize.x / 2.0f,
			+_spriteSize.y * 0.0f,
			(_textureCoords.x + _textureCoordSize.x * 0.0f) / m_TextureSize.x,
			1.0f - (_textureCoords.y + _textureCoordSize.y * 1.0f) / m_TextureSize.y,
		}; 
		
		m_GraphicsData.insert(m_GraphicsData.end(), frameData.begin(), frameData.end());
	}

	void AnimatedSprite::generate(void) {
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_GraphicsData.size(), m_GraphicsData.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)(2 * sizeof(float)));
	}

	void AnimatedSprite::setAnimationIndex(unsigned int _index) {
		m_AnimationIndex = _index;
	}
}