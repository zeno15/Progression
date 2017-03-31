#ifndef INCLUDED_DRILLER_COMPONENTS_RENDER_COMPONENT_HPP_
#define INCLUDED_DRILLER_COMPONENTS_RENDER_COMPONENT_HPP_

#include <ECS/Component.hpp>

#include <Graphics/Renderable.hpp>

namespace Window {
	class Window;
}

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Component able to be rendered
	///
	////////////////////////////////////////////////////////////
	class RenderComponent : ECS::Component {
	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The entity id
		///
		////////////////////////////////////////////////////////////
		RenderComponent(unsigned int _entityId);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		///	\param	The entity id
		///
		///	\param	Pointer to the renderable object
		///
		////////////////////////////////////////////////////////////
		RenderComponent(unsigned int _entityId, Graphics::Renderable *_renderable);
		////////////////////////////////////////////////////////////
		///
		///	\brief	Renders the scene
		///
		///	\param	The window to draw on
		///
		///	\param	The states to draw with
		///
		////////////////////////////////////////////////////////////
		void render(const Window::Window& _window, Graphics::RenderData _renderData) const;

		Graphics::Renderable *renderable;		///<		Pointer to renderable object to draw
	};

}

#endif // INCLUDED_DRILLER_COMPONENTS_RENDER_COMPONENT_HPP_