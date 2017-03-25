#include <Infrastructure/ShaderManager.hpp>

#include <iostream>

namespace Infrastructure {
	const std::string ShaderManager::Name = "ShaderManager";

	bool ShaderManager::addShader(const std::string& _name, const std::string& _vertexPath, const std::string& _fragmentPath) {
		for (unsigned int i = 0; i < m_Shaders.size(); i += 1) {
			if (m_Shaders.at(i).first == _name) {
				return true;
			}
		}

		m_Shaders.push_back(std::pair<std::string, Graphics::Shader>(_name, Graphics::Shader()));

		m_Shaders.back().second.loadVertexShader(_vertexPath);
		m_Shaders.back().second.loadFragmentShader(_fragmentPath);

		if (!m_Shaders.back().second.compileShader()) {
			std::cerr << m_Shaders.back().second.getCompileError() << std::endl;

			m_Shaders.erase(m_Shaders.begin() + m_Shaders.size() - 1);

			return false;
		}

		return true;
	}
	bool ShaderManager::addShaderFromSource(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource) {
		for (unsigned int i = 0; i < m_Shaders.size(); i += 1) {
			if (m_Shaders.at(i).first == _name) {
				return true;
			}
		}

		m_Shaders.push_back(std::pair<std::string, Graphics::Shader>(_name, Graphics::Shader()));

		m_Shaders.back().second.loadShadersFromStrings(_vertexSource, _fragmentSource);

		if (!m_Shaders.back().second.compileShader()) {
			std::cerr << m_Shaders.back().second.getCompileError() << std::endl;

			m_Shaders.erase(m_Shaders.begin() + m_Shaders.size() - 1);

			return false;
		}

		return true;
	}
	bool ShaderManager::addVGFShader(const std::string& _name, const std::string& _vertexPath, const std::string& _geometryPath, const std::string& _fragmentPath) {
		for (unsigned int i = 0; i < m_Shaders.size(); i += 1) {
			if (m_Shaders.at(i).first == _name) {
				return true;
			}
		}

		m_Shaders.push_back(std::pair<std::string, Graphics::Shader>(_name, Graphics::Shader()));


		m_Shaders.back().second.loadVGFShaders(_vertexPath, _geometryPath, _fragmentPath);

		if (!m_Shaders.back().second.compileShader()) {
			std::cerr << "Shader failed to load: " << std::endl;
			std::cerr << m_Shaders.back().second.getCompileError() << std::endl;

			m_Shaders.erase(m_Shaders.begin() + m_Shaders.size() - 1);

			return false;
		}

		return true;
	}

	Graphics::Shader& ShaderManager::getShader(const std::string& _name) {
		for (unsigned int i = 0; i < m_Shaders.size(); i += 1) {
			if (m_Shaders.at(i).first == _name) {
				return m_Shaders.at(i).second;
			}
		}

		throw std::runtime_error(std::string("Shader \"" + _name + "\" not present in ShaderManager."));
	}
}