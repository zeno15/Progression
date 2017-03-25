#ifndef INCLUDED_INFRASTRUCTURE_SHADER_MANAGER_HPP_
#define INCLUDED_INFRASTRUCTURE_SHADER_MANAGER_HPP_

#include <Infrastructure/Manager.hpp>

#include <Graphics/Shader.hpp>

#include <vector>

////////////////////////////////////////////////////////////
///
///	\namespace Infrastructure
///
////////////////////////////////////////////////////////////
namespace Infrastructure {
	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to handle shader management
	///
	////////////////////////////////////////////////////////////
	class ShaderManager : public Manager {
	public:
		friend class InstanceCollection;

		const static std::string Name;			///<	Name of the manager

		////////////////////////////////////////////////////////////
		//
		//	Adds a shader to the manager by their file paths
		//
		////////////////////////////////////////////////////////////
		bool addShader(const std::string& _name, const std::string& _vertexPath, const std::string& _fragmentPath);
		////////////////////////////////////////////////////////////
		//
		//	Adds a shader to the manager by their file paths, with geometry
		//
		////////////////////////////////////////////////////////////
		bool addVGFShader(const std::string& _name, const std::string& _vertexPath, const std::string& _geometryPath, const std::string& _fragmentPath);
		////////////////////////////////////////////////////////////
		//
		//	Adds a shader to the manager by their sources
		//
		////////////////////////////////////////////////////////////
		bool addShaderFromSource(const std::string& _name, const std::string& _vertexSource, const std::string& _fragmentSource);
		////////////////////////////////////////////////////////////
		//
		//	Returns the requested shader
		//
		////////////////////////////////////////////////////////////
		Graphics::Shader& getShader(const std::string& _name);

	private:

		std::vector<std::pair<std::string, Graphics::Shader>>		m_Shaders;		///<	The stored shaders
	};
}

#endif // INCLUDED_INFRASTRUCTURE_SHADER_MANAGER_HPP_