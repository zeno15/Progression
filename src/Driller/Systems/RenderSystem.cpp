#include <Driller/Systems/RenderSystem.hpp>

#include <System/Mat4x4.hpp>

namespace Driller {

	void RenderSystem::renderable(Window::Window& _window, Graphics::RenderData _states) const {

		for (auto& e : m_SystemEntities) {
			auto components = e->getComponents<TransformationComponent, RenderComponent>();

			if (std::get<1>(components)->renderable) {
				_states.model = ::System::Mat4x4::createTranslation(::System::Vector3f(std::get<0>(components)->position, 0.0f));

				std::get<1>(components)->renderable->render(_window, _states);
			}
		}
	}
}