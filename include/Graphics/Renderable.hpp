#ifndef INCLUDED_GRAPHICS_RENDERABLE_HPP_
#define INCLUDED_GRAPHICS_RENDERABLE_HPP_

#include <Graphics/RenderData.hpp>
#include <Window/Window.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace	Graphics
///
////////////////////////////////////////////////////////////
namespace Graphics {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Abstract class to allow for generic rendering
	///
	////////////////////////////////////////////////////////////
	class Renderable {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Pure virtual method to override to allow rendering
		///
		///	\param	The window to render to
		///
		///	\param	The render states to use
		///
		////////////////////////////////////////////////////////////
		virtual void render(const Window::Window& _window, RenderData _RenderData) const = 0;
	};
}

#endif // INCLUDED_GRAPHICS_RENDERABLE_HPP_