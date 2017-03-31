#include <Pong/Scenes/PongGameScene.hpp>

namespace Pong {

	PongGameScene::PongGameScene(void) :
		Scene("PongGameScene") {

	}
	PongGameScene::~PongGameScene(void) {

	}

	void PongGameScene::update(float _delta) {
	}

	bool PongGameScene::handleEvent(const System::Event& _event) {
		return false;
	}

	void PongGameScene::render(const Window::Window& _window, Graphics::RenderData _renderData) const {

	}
}