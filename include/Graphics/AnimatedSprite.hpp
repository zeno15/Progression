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

		////////////////////////////////////////////////////////////
		///
		///	\brief	Clears the current animations
		///
		////////////////////////////////////////////////////////////
		void clearAnimations(void);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds an animation frame
		///
		///	\param	The size of the sprite
		///
		///	\param	The texture coordinates
		///
		////////////////////////////////////////////////////////////
		void addAnimation(const System::Vector2f& _spriteSize, const System::Vector2f& _textureCoords);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Adds an animation frame
		///
		///	\param	The size of the sprite
		///
		///	\param	The texture coordinates
		///
		///	\param	The size of the texture to map
		///
		////////////////////////////////////////////////////////////
		void addAnimation(const System::Vector2f& _spriteSize, const System::Vector2f& _textureCoords, const System::Vector2f& _textureCoordSize);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Generates the OpenGL graphics
		///
		////////////////////////////////////////////////////////////
		void generate(void);

		////////////////////////////////////////////////////////////
		///
		///	\brief	Sets the animation index
		///
		///	\param	The index
		///
		////////////////////////////////////////////////////////////
		void setAnimationIndex(unsigned int _index);

	private:
		System::Vector2f		m_TextureSize;				///<	The size of the texture

		std::string				m_TextureName;				///<	The name of the sprite texture

		std::vector<float>		m_GraphicsData;				///<	The graphics data

		unsigned int			m_VAO;						///<	OpenGL VAO handle
		unsigned int			m_VBO;						///<	OpenGL position VBO handle
		unsigned int			m_AnimationIndex;			///<	The current frame of the animated sprite
	};
}

#endif // INCLUDED_GRAPHICS_ANIMATED_SPRITE_HPP_