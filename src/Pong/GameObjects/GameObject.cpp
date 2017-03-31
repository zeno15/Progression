#include <Pong/GameObjects/GameObject.hpp>

namespace Pong {
	GameObject::GameObject(void) :
		GameObject(std::string()) {

	}
	GameObject::GameObject(const std::string& _name) :
		m_Name(_name) {

	}

	GameObject::~GameObject(void) {

	}

	const std::string& GameObject::getName(void) const {
		return m_Name;
	}
}