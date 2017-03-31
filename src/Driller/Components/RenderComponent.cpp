#include <Driller/Components/RenderComponent.hpp>

#include <Window/Window.hpp>

namespace Driller {
	RenderComponent::RenderComponent(unsigned int _entityId) :
		RenderComponent(_entityId, nullptr) {
	}
	RenderComponent::RenderComponent(unsigned int _entityId, Graphics::Renderable *_renderable) :
		ECS::Component(_entityId),
		renderable(_renderable) {
	}

	void RenderComponent::render(const Window::Window& _window, Graphics::RenderData _renderData) const {
		if (renderable != nullptr) {
			renderable->render(_window, _renderData);
		}
	}
}