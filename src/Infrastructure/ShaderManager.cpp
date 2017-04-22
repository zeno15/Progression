#include <Infrastructure/ShaderManager.hpp>

#include <iostream>

namespace {
	const std::string vertexArrayNonTexturedVertex = R"(
#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec4 in_Colour;

uniform mat4 MVP = mat4(1.0f);

out vec4 frag_Colour;

void main() {
	gl_Position = MVP * vec4(in_Position, 1.0);
	frag_Colour = in_Colour;
}
)"; 
	const std::string vertexArrayNonTexturedFragment = R"(
#version 330

in vec4 frag_Colour;
out vec4 out_FragColour;

void main() {
	out_FragColour = frag_Colour;
}	
)";

	const std::string textVertex = R"(
#version 330

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 tex;

uniform mat4 MVP = mat4(1.0f);
uniform vec2 TexSize;
uniform vec4 Colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec2 texUV;
out vec3 col;

void main() {
	gl_Position = MVP * vec4(vp, 0.0, 1.0);
	texUV.x = tex.x / TexSize.x;
	texUV.y = (TexSize.y - tex.y) / TexSize.y;
	col = Colour.rgb;
}
)";
	const std::string textFragment = R"(
#version 330

in vec2 texUV;
in vec3 col;

uniform sampler2D tex;

out vec4 frag_colour;
void main() {
	frag_colour = vec4(col, texture(tex, texUV).r);
}
)";
}

namespace Infrastructure {
	const std::string ShaderManager::Name = "ShaderManager";
	const std::string ShaderManager::NonTexturedVertexArrayShaderName = "_SystemGraphicsVertexArrayNonTextured";
	const std::string ShaderManager::NonTexturedVertexArrayShaderMVPName = "MVP";

	const std::string ShaderManager::TextShaderName = "_SystemTextShader";
	const std::string ShaderManager::TextShaderMVPName = "MVP";
	const std::string ShaderManager::TextShaderTexSizeName = "TexSize";
	const std::string ShaderManager::TextShaderColourName = "Colour";

	void ShaderManager::initialiseSystemShaders(void) {
		addShaderFromSource(NonTexturedVertexArrayShaderName, vertexArrayNonTexturedVertex, vertexArrayNonTexturedFragment);
		getShader(NonTexturedVertexArrayShaderName).getLocationOfUniform(NonTexturedVertexArrayShaderMVPName);


		addShaderFromSource(TextShaderName, textVertex, textFragment);
		getShader(TextShaderName).getLocationOfUniforms({
			TextShaderMVPName,
			TextShaderTexSizeName,
			TextShaderColourName
		});
	}

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