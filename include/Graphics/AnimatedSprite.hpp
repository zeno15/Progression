#ifndef INCLUDED_GRAPHICS_ANIMATED_SPRITE_HPP_
#define INCLUDED_GRAPHICS_ANIMATED_SPRITE_HPP_

#include <Graphics/Renderable.hpp>

#include <System/Transformable2D.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	Graphics
///
////////////////////////////////////////////////////////////
namespace Graphics {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to represent an animated 2D sprite
	///
	////////////////////////////////////////////////////////////
	class AnimatedSprite : public Renderable, public System::Transformable2D {
	public:
		////////////////////////////////////////////////////////////
		///	
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		AnimatedSprite(void);
		////////////////////////////////////////////////////////////
		///	
		///	\brief	Constructor
		///
		///	\param	The name of the texture to render with
		///
		////////////////////////////////////////////////////////////
		AnimatedSprite(const std::string& _textureName);
		////////////////////////////////////////////////////////////
		///	
		///	\brief	Destructor
		///
		////////////////////////////////////////////////////////////
		~AnimatedSprite(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the sprite
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, RenderData _renderData) const override;

		void clearAnimations(void);
		void addAnimation(const System::Vector2f& _spriteSize, const System::Vector2f& _textureCoords);

	private:
		std::string				m_TextureName;				///<	The name of the sprite texture

		std::vector<float>		m_GraphicData;				///<	The position and texture data

		unsigned int			m_VAO;						///<	OpenGL VAO handle
		unsigned int			m_VBO;						///<	OpenGL position VBO handle
	};
}

#endif // INCLUDED_GRAPHICS_ANIMATED_SPRITE_HPP_