#include <Infrastructure/Scene.hpp>

namespace Infrastructure {

	Scene::Scene(const std::string& _name) :
		m_Name(_name) {

	}
	Scene::~Scene() {

	}

	std::string Scene::getName(void) const {
		return m_Name;
	}

}