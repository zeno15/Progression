#ifndef INCLUDED_DRILLER_SYSTEMS_RENDER_SYSTEM_HPP_
#define INCLUDED_DRILLER_SYSTEMS_RENDER_SYSTEM_HPP_

#include <ECS/System.hpp>

#include <Driller/Components/RenderComponent.hpp>
#include <Driller/Components/TransformationComponent.hpp>

////////////////////////////////////////////////////////////
///
///	\namespace Driller
///
////////////////////////////////////////////////////////////
namespace Driller {

	////////////////////////////////////////////////////////////
	///
	///	\brief	System that can draw RenderComponents
	///
	////////////////////////////////////////////////////////////
	class RenderSystem : ECS::System<RenderComponent, TransformationComponent> {
	public:
		////////////////////////////////////////////////////////////
		///
		/// \brief  Draws all entities within the system.
		///
		/// \param  The render _target
		///
		/// \param  The render _states
		///
		////////////////////////////////////////////////////////////
		virtual void renderable(Window::Window& _window, Graphics::RenderData _states) const override;
	};
}

#endif // INCLUDED_DRILLER_SYSTEMS_RENDER_SYSTEM_HPP_